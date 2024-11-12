#include "buddy.h"
#include "assert.h"
#include "list.h"
#include "paging.h"

struct free_area free_area = {0};


// store the start and end of kernel image so we dont' accidently free these pages
extern uint64_t kernel64_start;
extern uint64_t kernel64_end;

// takes a list head and extracts the page_struct out of it
static inline struct page_struct * list_to_page(struct list_head * list){
    return list_entry(list, struct page_struct, list);
}

// returns list attribute of page 
static inline struct list_head * page_to_list(struct page_struct * page){
    return &page->list;
}


// the page_order is incremented by 1 as we store order 0 as 1 so unfreed pages can be stored as 0 has nice side effect of returning order of 0-MAX_ORDER and -1 for not freed 
static inline void set_page_order(struct page_struct * page, u64 order){
    page->flags |=  (((order + 1)& PAGE_ORDER_MASK) << PAGE_ORDER);
}

static inline void clear_page_order(struct page_struct* page) {
    set_page_order(page, -1);
}


// returns 0-MAX_ORDER if page is allocated and -1 if free 
static inline u64 get_page_order(struct page_struct * page){
    return ((page->flags >> PAGE_ORDER) & PAGE_ORDER_MASK) - 1;

}

static inline void remove_page_in_list(struct page_struct *page){
    DELETE_LIST_HEAD(page_to_list(page));
}

static inline void add_page_to_order(struct page_struct * page, u64 order){
    set_page_order(page, order);
    ADD_LIST(GET_ORDER_HEAD(order), page_to_list(page));
}

static inline u64 get_buddy(u64 pfn, u32 order){
    return pfn ^ (1 << order);
}

// returns the largest order size will fill up 
u64 page_order(u64 size){
    if(size >> PAGE_SHIFT == 0){
        return 0;
    }
    // counts the number of leading zero's and adds PAGE_SHIFT to account for order 0 being page_shift 
    u64 index = __builtin_clz(size) + PAGE_SHIFT;
    return 31-index;
}


void init_free_area(){
    for(u32 i = 0; i <= MAX_ORDER; i++){
        INIT_LIST_HEAD(&free_area.orders[i]);
    }
}


void print_free_area() {
    for(uint32_t order = 0; order<=MAX_ORDER; order++) {
        struct list_head* head = GET_ORDER_HEAD(order);
        struct list_head* pos;
        printf("ORDER %d, SIZE: %#x\n", order, ORDER_TO_SIZE(order));
        list_for_each(head, pos) {
            struct page_struct* page= list_to_page(pos);
            printf("\t%#x\n", PAGE_TO_PHYS(page));
        }
    }
}


// Initailizes the page's in this range by setting flags and address
void init_page_structs(u64 start_addr, u64 len){
    for(u64 current = start_addr; current < start_addr + len; current += PAGE_SIZE){
        /*ASSERT(current > (4UL * GIGABYTE), "System only supports up to 4B of memory");*/
        struct page_struct * page= PHYS_TO_PAGE(current);
        page->flags = 0;
        page->address = current; 
        INIT_LIST_HEAD(&page->list);
    }
}

// function free's all unused memory to free_area
void init_memory(struct kernel_32_info* info, multiboot_info_t* multiboot){
   init_free_area(); 

    // loop over memory regions specificed by mutliboot_info 
    ASSERT(!(multiboot->flags & (1 << 6)), "mmap_* fields are invalid, no memory found");
    struct multiboot_mmap_entry* base = (struct multiboot_mmap_entry*)(u64)multiboot->mmap_addr;

    u64 entry_count = multiboot->mmap_length / sizeof(struct multiboot_mmap_entry);
    for(u32 i = 0; i < entry_count; i++){
        if(base[i].type != MULTIBOOT_MEMORY_AVAILABLE){
            continue;
        }
        // round size UP to nearest page
        u64 start = base[i].addr;
        ALIGN(start, PAGE_SHIFT);
        u64 end = base[i].addr + base[i].len;
        // must clear lower 12 bits of len as multiboot is NOT page aligned
        u64 len = base[i].len & (~PAGE_MASK);
        printf("%#lx, %#lx\n", start, len);
        if(start + len > (4ul * GIGABYTE)){
            ASSERT(start > (4ul * GIGABYTE), "Multiboot start value is greater than 4GB");
            len = (4ul * GIGABYTE) - start;
        }
        init_page_structs(start, len);
        free_page_range(start, len);
    }
    print_free_area();
}

u64 free_pages(struct page_struct * page, u64 order){
    u64 pfn = PAGE_TO_PFN(page);
    u64 buddy_pfn = get_buddy(pfn, order);
    struct page_struct * buddy_page = PFN_TO_PAGE(buddy_pfn);
    u64 buddy_order = get_page_order(buddy_page);

    if(order >= MAX_ORDER){
        // if MAX_ORDER no more orders to merge into 
        goto base_case;
    }

    // if buddy is NOT freed OR not the same order, just add buddy and exit
    if(buddy_order == order){
        struct page_struct * head_page = PFN_TO_PAGE(MIN(pfn, buddy_pfn));
        struct page_struct * tail_page = PFN_TO_PAGE(MAX(pfn, buddy_pfn));
        // first free and page is second means the page is NOT in a list so check to avoid freeing item that's not in a list 
        if(get_page_order(tail_page) != -1){
            remove_page_in_list(tail_page);
        }
        free_pages(head_page, order +1);
        return 0;
    };
 
base_case:
    add_page_to_order(page, order);
    return 0;
}

u64 free_page_range(u64 page_addr, u64 page_len){
    u64 current = page_addr;
    while(page_len != 0){
        u64 order = MIN(page_order(page_len), MAX_ORDER) ;
        u64 page_size =  ORDER_TO_SIZE(order);
        struct page_struct * page = PHYS_TO_PAGE(current);

        free_pages(page, order);

        page_len -= page_size;
        current += page_size;
    }
    return 0;
}

// function assumes that page will be deleted later, only responsible for breaking and inserting buddy pages
struct page_struct * break_pages_to_order(struct page_struct *page, u32 current_order, u32 target_order){
    printf("Attempting to break page @ %#lx curr order %d target order %d\n", PAGE_TO_PHYS(page), current_order, target_order);
    ASSERT(current_order < target_order, "Current order must be smaller than target order");

    // correct order, don't break just return
    if(current_order == target_order){
        return page;
    }
    u64 pfn = PAGE_TO_PFN(page);
    u64 buddy_pfn = get_buddy(pfn, current_order-1);
    struct page_struct * buddy_page = PFN_TO_PAGE(buddy_pfn);

    struct list_head * head = GET_ORDER_HEAD(current_order - 1);
    ADD_LIST(head, page_to_list(buddy_page));
    // set the buddy order
    set_page_order(buddy_page, current_order - 1);

    return break_pages_to_order(page, current_order -1, target_order);
}

struct page_struct * __allocate_page(u32 order){
    if(order > MAX_ORDER){
        return NULL;
    }
    struct page_struct * free_page = NULL;
    u32 page_order = order; 
    // empty page of order is free, jsut return it
    struct list_head * order_list = GET_ORDER_HEAD(order);
    if(!list_empty(order_list)){
        free_page = list_to_page(list_pop(order_list));
    }else{
        while(++page_order <= MAX_ORDER){
            struct list_head * order_list = GET_ORDER_HEAD(page_order);
            if(!list_empty(order_list)){
                free_page = list_to_page(list_pop(order_list));
                break;
            }
        }
    }
    // no more free memory 
    ASSERT(!free_page, "No more memory left in system");
    free_page = break_pages_to_order(free_page, page_order, order);
    clear_page_order(free_page);
    return free_page;
}

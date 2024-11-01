#include <stdint.h>
#include <stdbool.h>
#include "list.h"

#include "paging.h"
#include "buddy.h"

#include "printf.h"
#include "multiboot.h"
#include "kernel32.h"
#include "assert.h"


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
    for(u32 i = 0; i < MAX_ORDER; i++){
        INIT_LIST_HEAD(&free_area.orders[i]);
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
        u64 start = base[i].addr;
        u64 end = base[i].addr + base[i].len;
    }
}


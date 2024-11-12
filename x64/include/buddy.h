#ifndef __BUDDY_H
#define __BUDDY_H

#include <stdint.h>
#include <stdbool.h>


#include "types.h"
#include "paging.h"
#include "list.h"

#include "printf.h"
#include "multiboot.h"
#include "kernel32.h"
#include "assert.h"
#include "math.h"


/*#define ORDER_TO_SIZE(order) (PAGE_SIZE * 2 ** order)*/
#define ORDER_TO_SIZE(order) (1 << (order + PAGE_SHIFT))  // same as above but uses more efficent bit shift math



// Max order of buddy sizes is 11, so max size if 0x1000 * 2 ** 11
#define MAX_ORDER 11
struct free_area{
    struct list_head orders[MAX_ORDER+1];
};

// returns a pointer to start of list_head in order
#define GET_ORDER_HEAD(order) (&(free_area.orders[order]))

u64 page_order(u64 size);
void init_free_area();

void init_page_structs(u64 start_addr, u64 len);

void init_memory(struct kernel_32_info* info, multiboot_info_t* multiboot);
u64 free_pages(struct page_struct * page, u64 order);

u64 free_page_range(u64 page_addr, u64 page_len);

struct page_struct * break_pages_to_order(struct page_struct *page, u32 current_order, u32 target_order);
struct page_struct * __allocate_page(u32 order);

void print_free_area();
#endif

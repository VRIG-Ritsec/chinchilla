#ifndef __BUDDY_H
#define __BUDDY_H

#include "types.h"
#include "list.h"

#define PAGE_SHIFT 12 
#define PAGE_SIZE (1<< PAGE_SHIFT)
#define PAGE_MASK (PAGE_SIZE - 1)

// Align it so we can fit equally in pages so each page can hold the same amount 
struct __attribute__((aligned(32))) page_struct{
    u32 flags; 
    // Virt addr of the page 
    u64 address;
    struct list_head list;
};

#endif

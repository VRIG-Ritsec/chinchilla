#ifndef __PAGING_H
#define __PAGING_H

#include "utils/types.h"
#include "utils/list.h"

#include <stdint.h>
#include <stdbool.h>
#include "utils/printf.h"
#include "kernel/multiboot.h"
#include "kernel/kernel32.h"

#define PAGE_SHIFT 12 
#define PAGE_SIZE (1<< PAGE_SHIFT)
#define PAGE_MASK (PAGE_SIZE - 1)

#define PAGE_DESC_COUNT (PAGE_SIZE / sizeof(u64*))


// Page Table Flags
#define PG_PRESENT (1<<0)
#define PG_RW      (1<<1)
#define PG_PS      (1<<7) // for block addressing



// Align it so we can fit equally in pages so each page can hold the same amount 
struct __attribute__((aligned(32))) page_struct{
    u64 flags; 
    // Virt addr of the page 
    u64 address;
    struct list_head list;
};

// page_struct flags 
#define PAGE_ORDER 60 
#define PAGE_ORDER_BITS 4
#define PAGE_ORDER_MASK ((1 << PAGE_ORDER_BITS) -1)


#define SYSTEM_MAX_MEMORY (4ul * GIGABYTE)   // our system only supports 4GB of memory
#define PAGE_STRUCTS_NEEDED (SYSTEM_MAX_MEMORY >> PAGE_SHIFT)

extern struct page_struct page_array[PAGE_STRUCTS_NEEDED]; //we support up to 4G of memory

#define PFN_TO_PHYS(pfn) (pfn << PAGE_SHIFT)
#define PFN_TO_PAGE(pfn) (&page_array[pfn])


#define PAGE_TO_PFN(page) ((struct page_struct * )page - (struct page_struct * )&page_array)
#define PAGE_TO_PHYS(page) ((void*)PFN_TO_PHYS(PAGE_TO_PFN(page)))
#define PAGE_TO_VIRT(page) PAGE_TO_PHYS(page)

#define PHYS_TO_PFN(addr) (addr >> PAGE_SHIFT)
#define PHYS_TO_PAGE(addr) (PFN_TO_PAGE(PHYS_TO_PFN(addr)))


#endif

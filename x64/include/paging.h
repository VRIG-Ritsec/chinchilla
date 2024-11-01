#ifndef __PAGING_H
#define __PAGING_H

#include "types.h"
#include "list.h"

#define PAGE_SHIFT 12 
#define PAGE_SIZE (1<< PAGE_SHIFT)
#define PAGE_MASK (PAGE_SIZE - 1)

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
#define PAGE_ARRAY_LEN (PAGE_STRUCTS_NEEDED * sizeof(struct page_struct))

extern struct page_struct page_array[PAGE_ARRAY_LEN]; //we support up to 4G of memory

#define PFN_TO_PHYS(pfn) (pfn << PAGE_SHIFT)
#define PFN_TO_PAGE(pfn) (&page_array[pfn])


#define PAGE_TO_PFN(page) ((struct page_struct * )page - (struct page_struct * )&page_array)
#define PAGE_TO_PHYS(page) (PFN_TO_PHYS(PAGE_TO_PFN(page)))

#define PHYS_TO_PFN(addr) (addr >> PAGE_SHIFT)
#define PHYS_TO_PAGE(addr) (PFN_TO_PAGE(PHYS_TO_PFN(addr)))



#endif

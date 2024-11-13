#ifndef __PAGING_H
#define __PAGING_H

void *init_page_table();

#define PG_PRESENT (1 << 0)
#define PG_RW (1 << 1)
#define PG_PS (1 << 7) // used for block addressing

#define PAGE_SIZE 0x1000
#define TWO_M (PAGE_SIZE * 0x200)

// creates valid entires for page table's
#define PGD_ENTRY(val) (val | PG_PRESENT | PG_RW)
#define PUD_ENTRY(val) (val | PG_PRESENT | PG_RW | PG_PS)

#endif

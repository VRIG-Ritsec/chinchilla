#ifndef __PAGING_H
#define __PAGING_H

void * init_page_table();

#define PG_PRESENT 1
#define PG_WRITE (1<<1)
#define PG_PS (1 << 7)  // used for block addressing 

#define PAGE_SIZE 0x1000
#define TWO_M (PAGE_SIZE * 0x200)


#endif

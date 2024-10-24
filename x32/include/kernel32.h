#ifndef __KERNEL_32
#define __KERNEL_32

/* 
* We use this struct to pass info between states and modes
*/
struct kernel_32_info {
    uint32_t page_table_start; //reserved
    uint32_t page_table_end;
    uint32_t multiboot_info; //multiboot info
};


#endif

#ifndef __KERNEL_32
#define __KERNEL_32

#include <stdint.h>

struct kernel_32_info {
    uint32_t kernel32_reserved_start;
    uint32_t kernel32_reserved_end;
    uint32_t multiboot_info; // multiboot info
};

#endif

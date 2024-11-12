#include <stdint.h>
#include <stdbool.h>
#include "printf.h"
#include "multiboot.h"
#include "buddy.h"
#include "paging.h"


int main64(struct kernel_32_info* ptr) {
    struct kernel_32_info info = *ptr;
    multiboot_info_t multiboot_info = *(multiboot_info_t*)(uint64_t)info.multiboot_info;
    init_memory(&info, &multiboot_info);

    printf("hello world from 64 bit!\n");
    struct page_struct * page = __allocate_page(0);
    print_free_area();
    struct page_struct * page2 = __allocate_page(0);
    print_free_area();
    printf("DONE\n");
    for(;;) {}
}

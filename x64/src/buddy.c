#include <stdint.h>
#include <stdbool.h>
#include "list.h"

#include "paging.h"
#include "buddy.h"

#include "printf.h"
#include "multiboot.h"
#include "kernel32.h"


struct free_area free_area = {0};


// store the start and end of kernel image so we dont' accidently free these pages
extern uint64_t kernel64_start;
extern uint64_t kernel64_end;

// function takes a list head and extracts the page_struct out of it
static inline struct page_struct * list_page(struct list_head * list){
    return list_entry(list, struct page_struct, list);
}

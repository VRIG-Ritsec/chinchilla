#include <stdbool.h>
#include <stdint.h>
#include "paging.h"

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;

#define WRITE64(ptr, val) *((u64*)(ptr)) = (val)
#define READ64(ptr)*(u64*)(ptr)
// macro for adding flags that page table entries need to be valid
#define PG_ENTRY(ptr) (((uint64_t)(uint32_t)ptr) | PG_PRESENT | PG_WRITE)


extern u64 page_table_start;
extern void die();


void * pgdir = &page_table_start;
void * free_page = &page_table_start + 0x1000;

void * get_new_page(){
    if (free_page >= (void*)&page_table_start + 0x10000){
        die();
    }
    free_page += 0x1000; 
    return free_page - 0x1000;
}

// this addresses 4_MB of memory from 0 to 4MB
void * init_page_table(){
    void * p4d = get_new_page();
    void * pud = get_new_page();
    // addresses for 0-2MB 
    void * pmd_1 = get_new_page();
    // addresses for 2MB-4MB
    void * pmd_2 = get_new_page();

    WRITE64(pgdir, PG_ENTRY(p4d));
    WRITE64(p4d, PG_ENTRY(pud));
    WRITE64(pud, PG_ENTRY(pmd_1));
    WRITE64(pud+sizeof(u64), PG_ENTRY(pmd_2));

    // map first 2MB of pages 
    for(u64 addr = 0, idx = 0; addr < TWO_M; addr+= PAGE_SIZE, idx+= 8){
        WRITE64(pmd_1+idx, PG_ENTRY(addr));
    }
    // map the next 2MB of memory
    for(u64 addr = TWO_M, idx = 0; addr < TWO_M*2; addr+= PAGE_SIZE, idx+= 8){
        WRITE64(pmd_2+idx, PG_ENTRY(addr));
    }

    return pgdir;
}

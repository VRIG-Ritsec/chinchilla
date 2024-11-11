#include "paging.h"


extern u64 kernel_pgd[PAGE_DESC_COUNT];
extern u64 kernel_pud[PAGE_DESC_COUNT];

// setup block addressing 
void init_64_bit_page_tables(){
    /*kernel_pgd[0] = MK_PGD_ENTRY(&kernel_pud);*/
    /*// loops per each gig*/
    /*for(u32 i = 0; i < 4; i++){*/
    /*    kernel_pud[i] = MK_PUD_ENTRY(i * GIGABYTE);*/
    /*}*/
}

#include "paging.h"
#include <stdbool.h>
#include <stdint.h>

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;

#define GIGABYTE (1 << 30)

#define WRITE64(ptr, val) *((u64 *)(ptr)) = (val)
#define READ64(ptr) *(u64 *)(ptr)
// macro for adding flags that page table entries need to be valid
#define PG_ENTRY(ptr) (((uint64_t)(uint32_t)ptr) | PG_PRESENT | PG_WRITE)

extern u64 kernel_pgd[512];
extern u64 kernel_pud[512];

extern void die();

// this addresses 4_MB of memory from 0 to 4MB
void *init_page_table() {
    kernel_pgd[0] = PGD_ENTRY((u32)&kernel_pud);
    // loops per each gig
    for (u32 i = 0; i < 512; i++) {
        kernel_pud[i] = PUD_ENTRY(i * GIGABYTE);
    }

    return &kernel_pgd;
}

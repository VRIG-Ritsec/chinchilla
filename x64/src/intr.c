#include "buddy.h"
#include "idt.h"
#include "paging.h"

struct page_struct *idt_page;
struct idt64 *idt64;


void isr_handler(u64 isr, u32 *error_code) { printf("FUCK"); }

void init_idt(void) {
    idt_page = allocate_page(PAGE_SIZE);
    idt64 = PAGE_TO_VIRT(idt_page);

    struct idt64 entry = IDT_TRAP_ENTRY((u64)&isr_handler);
}

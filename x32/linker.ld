ENTRY(_start)

SECTIONS {
    . = 1M;
	kernel32_start = .;

    .text BLOCK(4K) : ALIGN(4K)
    {
        *(.multiboot)
        *(.text)
    }
    
        /* Read-only data. */
    .rodata BLOCK(4K) : ALIGN(4K)
    {
        *(.rodata)
    }

    /* Read-write data (initialized) */
    .data BLOCK(4K) : ALIGN(4K)
    {
        *(.data)
    }

    /* Read-write data (uninitialized) and stack */
    .bss BLOCK(4K) : ALIGN(4K)
    {
        *(COMMON)
        *(.bss)
    }

    /* Creates a stack */ 
    . += 0x4000;
    stack_top = .;

    page_table_start = ALIGN(4k);
    . += 0x10000;
    page_table_end = ALIGN(4k);
	kernel32_end = .;
}

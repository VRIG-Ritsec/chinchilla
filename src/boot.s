; Declare constants for the multiboot header.
MBALIGN  equ  1 << 0            ; align loaded modules on page boundaries
MEMINFO  equ  1 << 1            ; provide memory map
FLAGS    equ  MBALIGN | MEMINFO ; this is the Multiboot 'flag' field
MAGIC    equ  0x1BADB002        ; 'magic number' lets bootloader find the header
CHECKSUM equ -(MAGIC + FLAGS)   ; checksum of above, to prove we are multiboot


; Constants for serial 
SERIAL_PORT equ 0x3f8 ; COM1 

section .multiboot
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM


extern stack_top
extern main 
section .text
global _start
_start:
    mov esp, stack_top
    ; Disable paging
    mov eax, cr0
    
    and eax, 0x7FFFFFFF
    mov cr0, eax
    ; Set the PAE enable bit in CR4(Bit 5)
    mov eax, cr4 
    or eax, 0b10000
    mov cr4, eax
    ; Load CR3 with the physical address of the PML4 (Level 4 Page Map)

    ; Enable long mode by setting the LME flag (bit 8) in MSR 0xC0000080 (aka EFER)
    mov ecx, 0xC0000080 
    rdmsr
    or eax, 0b10000000   ; eax has lower 32
    ;wrmsr
    ;
    ;;; Enable paging
    ;mov eax, cr0
    ;or eax, 0x80000000 
    ;mov cr4, eax

    call main
repeat:
    jmp repeat

global inb:
inb:
    mov dx, [esp + 4]
    in al, dx 
    ret

global outb; meaning of this?
outb:
    mov dx, [esp + 4] ; how does stack look?
    mov al, [esp + 8] ; how does stack look?
    ; esp is ret ad4dr 
    ; esp + 4 is value?
    out dx, al
    ret

global enable_pae
enable_pae:
    mov eax, cr4
    or eax, 1 << 5 
    mov cr4, eax
global die
die:
    hlt

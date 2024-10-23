; Declare constants for the multiboot header.
MBALIGN  equ  1 << 0            ; align loaded modules on page boundaries
MEMINFO  equ  1 << 1            ; provide memory map
FLAGS    equ  MBALIGN | MEMINFO ; this is the Multiboot 'flag' field
MAGIC    equ  0x1BADB002        ; 'magic number' lets bootloader find the header
CHECKSUM equ -(MAGIC + FLAGS)   ; checksum of above, to prove we are multiboot


; Constants for serial 
SERIAL_PORT equ 0x3f8 ; COM1 

; Contants for segment descriptor access bytes  
; https://wiki.osdev.org/Global_Descriptor_Table
PRESENT equ        1 << 7      ; Must be 1 for valid segment
PRIV_LEVEL equ     1 << 5      ; 2 bits for CPU Priv level 0-> Kernel 3-> Userspace
TYPE equ           1 << 4      ; 0 is segment reg, 1 is code/data
EXECUTE equ        1 << 3      ; 0 is data segment, 1 is code segment 
DIRECTION equ      1 << 2      ; For data: Grow up or down, For Code: Priv level to execute
READWRITE equ      1 << 1      ; For data: 0 -> no write, for code: 0 -> no read
ACCESS equ         1 << 0      ; Changed to 1 as access flag, keep as 1 unless otherwise needed


; Random bits 
PG_BIT equ         31 
PAE_BIT equ        5
LME_BIT equ        8 ; long mode enable

; MSR
EFER_MSR equ       0xC0000080


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
    push ebx ; this is a multiboot_info_t structure referenced in documentation for multiboot
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
global enter_long_mode 
; Function will be called with a pointer to pgdir 
enter_long_mode: 
    ; Load CR3 with the physical address of the PML4 (Level 4 Page Map)
    mov eax, [esp+4]
    mov cr3, eax

    ; Disable paging
    mov eax, cr0
    and eax, 0x7FFFFFFF
    mov cr0, eax

    call enable_pae 

    ; Enable long mode by setting the LME flag (bit 8) in MSR 0xC0000080 (aka EFER)
    mov ecx, EFER_MSR 
    rdmsr
    or eax, (1 << LME_BIT)    ; eax has lower 32
    wrmsr
    
    ;; Enable paging
    mov eax, cr0
    or eax, (1 << PG_BIT) 
    mov cr4, eax


global enable_pae
enable_pae:
    ; Set the PAE enable bit in CR4(Bit 5)
    mov eax, cr4
    or eax, 1 << PAE_BIT
    mov cr4, eax

global die
die:
    hlt

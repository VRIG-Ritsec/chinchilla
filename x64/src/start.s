
extern main64
extern stack_top

section .entry
global _start
_start:
    mov rsp, stack_top
    mov rax, 1 
    hlt 

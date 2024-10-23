
extern main64
extern stack_top

section .entry
global _start
_start:
    mov rsp, stack_top
    mov rdi, 0xffffffffffffffff
    mov rax, 0xffffffffffffffff
    mov rax, 1 
    hlt 

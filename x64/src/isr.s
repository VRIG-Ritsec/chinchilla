section .text

extern isr_handler

%macro PUSH_REGS 0
    push rdi 
    push rsi 
    push rdx
    push rcx
    push rbx
    push rax
    push rbp
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
%endmacro

%macro RESTORE_REGS 0
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rbp
    pop rax
    pop rbx
    pop rcx
    pop rdx
    pop rsi 
    pop rdi
%endmacro
%macro isr_entry_error 1
    PUSH_REGS
    mov rax, rsp ; save address of current stack as we need to align
    and rsp, ~0xff
    sub rsp, 512 ; create stack space for fxsave
    fxsave [rsp] 
    
    mov rdi, %1   ; error_number 
    mov rsi, rax  ; pointer to saved regs + iret stack(error code)
    mov rbx, rsi  ; callee saved reg as we need the stack after for cleanup
    call isr_handler
    fxrstor [rsp]
    mov rsp, rbx  ; restore saved ret + iret stack
    RESTORE_REGS 
    add rsp, 8
    iret
%endmacro

%macro isr_entry_no_error 1
    push 0 ; push 0 for the error code to show no error
    isr_entry_error 
%endmacro

isr_entry_error 1

section .text

extern isr_handler

%define IDT_DIVIDE_ERROR                0    ; Divide-by-zero Error
%define IDT_DEBUG                       1    ; Debug Exception
%define IDT_NMI_INTERRUPT               2    ; Non-maskable Interrupt
%define IDT_BREAKPOINT                  3    ; Breakpoint (INT3)
%define IDT_OVERFLOW                    4    ; Overflow (INTO instruction)
%define IDT_BOUND_RANGE_EXCEEDED        5    ; Bound Range Exceeded (BOUND instruction)
%define IDT_INVALID_OPCODE              6    ; Invalid Opcode (Undefined Opcode)
%define IDT_DEVICE_NOT_AVAILABLE        7    ; Device Not Available (No Math Coprocessor)
%define IDT_DOUBLE_FAULT                8    ; Double Fault
%define IDT_COPROCESSOR_SEGMENT_OVERRUN 9    ; Coprocessor Segment Overrun (reserved, no longer used)
%define IDT_INVALID_TSS                 10   ; Invalid TSS
%define IDT_SEGMENT_NOT_PRESENT         11   ; Segment Not Present
%define IDT_STACK_SEGMENT_FAULT         12   ; Stack-Segment Fault
%define IDT_GENERAL_PROTECTION_FAULT    13   ; General Protection Fault
%define IDT_PAGE_FAULT                  14   ; Page Fault
%define IDT_RESERVED                    15   ; Reserved (Intel-reserved, do not use)
%define IDT_X87_FLOATING_POINT_ERROR    16   ; x87 Floating-Point Error (Math Fault)
%define IDT_ALIGNMENT_CHECK             17   ; Alignment Check
%define IDT_MACHINE_CHECK               18   ; Machine Check
%define IDT_SIMD_FLOATING_POINT_ERROR   19   ; SIMD Floating-Point Exception
%define IDT_VIRTUALIZATION_EXCEPTION    20   ; Virtualization Exception
%define IDT_CONTROL_PROTECTION_EXCEPTION 21  ; Control Protection Exception (Intel CET)

%define IDT_EXCEPTION_RESERVED_MIN      22   ; Reserved exception vectors 22–31
%define IDT_EXCEPTION_RESERVED_MAX      31   ; Last reserved exception vector


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
    isr_entry_error %1
%endmacro

global isr_0
isr_0:
    isr_entry_no_error 0            ; Exception number 0 (Divide-by-zero Error)

global isr_1
isr_1:
    isr_entry_no_error 1            ; Exception number 1 (Debug Exception)

global isr_2
isr_2:
    isr_entry_no_error 2            ; Exception number 2 (Non-maskable Interrupt)

global isr_3
isr_3:
    isr_entry_no_error 3            ; Exception number 3 (Breakpoint)

global isr_4
isr_4:
    isr_entry_no_error 4            ; Exception number 4 (Overflow)

global isr_5
isr_5:
    isr_entry_no_error 5            ; Exception number 5 (Bound Range Exceeded)

global isr_6
isr_6:
    isr_entry_no_error 6            ; Exception number 6 (Invalid Opcode)

global isr_7
isr_7:
    isr_entry_no_error 7            ; Exception number 7 (Device Not Available)

global isr_8
isr_8:
    isr_entry_error 8               ; Exception number 8 (Double Fault)

global isr_9
isr_9:
    isr_entry_no_error 9            ; Exception number 9 (Coprocessor Segment Overrun)

global isr_10
isr_10:
    isr_entry_error 10              ; Exception number 10 (Invalid TSS)

global isr_11
isr_11:
    isr_entry_error 11              ; Exception number 11 (Segment Not Present)

global isr_12
isr_12:
    isr_entry_error 12              ; Exception number 12 (Stack-Segment Fault)

global isr_13
isr_13:
    isr_entry_error 13              ; Exception number 13 (General Protection Fault)

global isr_14
isr_14:
    isr_entry_error 14              ; Exception number 14 (Page Fault)

global isr_15
isr_15:
    isr_entry_no_error 15           ; Exception number 15 (Reserved)

global isr_16
isr_16:
    isr_entry_no_error 16           ; Exception number 16 (x87 Floating-Point Error)

global isr_17
isr_17:
    isr_entry_error 17              ; Exception number 17 (Alignment Check)

global isr_18
isr_18:
    isr_entry_no_error 18           ; Exception number 18 (Machine Check)

global isr_19
isr_19:
    isr_entry_no_error 19           ; Exception number 19 (SIMD Floating-Point Exception)

global isr_20
isr_20:
    isr_entry_no_error 20           ; Exception number 20 (Virtualization Exception)

global isr_21
isr_21:
    isr_entry_error 21              ; Exception number 21 (Control Protection Exception)


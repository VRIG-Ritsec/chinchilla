/*
 * include/idt.h 
 * Interrupt Descriptor Table structures and values
*/

#ifndef __IDT_H
#define __IDT_H

#include <stdint.h>
#include <stdbool.h>

#include "types.h"
#include "paging.h"
#include "list.h"

#include "printf.h"
#include "multiboot.h"
#include "kernel32.h"
#include "assert.h"
#include "math.h"

#include "assert.h"
#include "kernel.h"
#include "list.h"
#include "paging.h"
#include "buddy.h"


// Various bits that the IDT requires
#define IDT_PRESENT (1UL << 7)
#define IDT_TRAP_GATE 0xf
#define IDT_INTR_GATE 0xe

// Copied from https://wiki.osdev.org/Interrupt_Descriptor_Table
struct idt64{
   u16 offset_1;        // offset bits 0..15
   u16 selector;        // a code segment selector in GDT or LDT
   u8  ist;             // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
   u8  type_attributes; // gate type, dpl, and p fields
   u16 offset_2;        // offset bits 16..31
   u32 offset_3;        // offset bits 32..63
   u32 zero;            // reserved
};

// this structure is passed to the lidt instruction based off diagram here https://wiki.osdev.org/Interrupt_Descriptor_Table
struct __attribute__((packed)) idtr{
    u16 size; 
    u64 offset;
};

// Exception Vector Numbers, used to index the Interrupt Descriptor Table
// https://wiki.osdev.org/Exceptions
#define IDT_DIVIDE_ERROR               0    // Divide-by-zero Error
#define IDT_DEBUG                      1    // Debug Exception
#define IDT_NMI_INTERRUPT              2    // Non-maskable Interrupt
#define IDT_BREAKPOINT                 3    // Breakpoint (INT3)
#define IDT_OVERFLOW                   4    // Overflow (INTO instruction)
#define IDT_BOUND_RANGE_EXCEEDED       5    // Bound Range Exceeded (BOUND instruction)
#define IDT_INVALID_OPCODE             6    // Invalid Opcode (Undefined Opcode)
#define IDT_DEVICE_NOT_AVAILABLE       7    // Device Not Available (No Math Coprocessor)
#define IDT_DOUBLE_FAULT               8    // Double Fault
#define IDT_COPROCESSOR_SEGMENT_OVERRUN 9   // Coprocessor Segment Overrun (reserved, no longer used)
#define IDT_INVALID_TSS                10   // Invalid TSS
#define IDT_SEGMENT_NOT_PRESENT        11   // Segment Not Present
#define IDT_STACK_SEGMENT_FAULT        12   // Stack-Segment Fault
#define IDT_GENERAL_PROTECTION_FAULT   13   // General Protection Fault
#define IDT_PAGE_FAULT                 14   // Page Fault
#define IDT_RESERVED                   15   // Reserved (Intel-reserved, do not use)
#define IDT_X87_FLOATING_POINT_ERROR   16   // x87 Floating-Point Error (Math Fault)
#define IDT_ALIGNMENT_CHECK            17   // Alignment Check
#define IDT_MACHINE_CHECK              18   // Machine Check
#define IDT_SIMD_FLOATING_POINT_ERROR  19   // SIMD Floating-Point Exception
#define IDT_VIRTUALIZATION_EXCEPTION   20   // Virtualization Exception
#define IDT_CONTROL_PROTECTION_EXCEPTION 21 // Control Protection Exception (Intel CET)

#define IDT_EXCEPTION_RESERVED_MIN     22   // Reserved exception vectors 22–31
#define IDT_EXCEPTION_RESERVED_MAX     31   // Last reserved exception vector

// @TODO Why does selector need to be 8 
#define IDT_ENTRY(offset, attribute)                                           \
    (struct idt64){.offset_1 = (offset) & 0xffff,                                            \
     .selector = 8,                                                            \
     .ist = 0,                                                                 \
     .type_attributes = IDT_PRESENT | attribute,                               \
     .offset_2 = ((offset) >> 16) & 0xffff,                                    \
     .offset_3 = ((offset) >> 32),                                             \
     .zero = 0}

// used to handle expcetions, occur to running software, synchronously 
#define IDT_TRAP_ENTRY(offset) IDT_ENTRY(offset, IDT_TRAP_GATE)
// done by devices and interrupt's the program, async
#define IDT_INTR_ENTRY(offset) IDT_ENTRY(offset, IDT_INTR_GATE)

// https://pdos.csail.mit.edu/6.828/2008/readings/i386/s09_06.htm
struct iret_stack{
    u64 error_code;
    u64 old_rip; 
    u64 old_cs; // made bigger due to hole, really is 16 bit 
    u64 old_rflags;
    u64 old_rsp;
    u64 old_ss;

};

struct isr_save_state{
    u64 r15;
    u64 r14;
    u64 r13;
    u64 r12;
    u64 r11;
    u64 r10;
    u64 r9;
    u64 r8;
    u64 rbp;
    u64 rax;
    u64 rbx;
    u64 rcx;
    u64 rdx;
    u64 rsi;
    u64 rdi;
    struct iret_stack iret_stack;
};

#define EXCEPTION_ENTRY(exception_number) EXPAND_AND_CONCAT(isr_, exception_number)
#define EXCEPTION_ENTRY_PTR(exception_number) (&EXCEPTION_ENTRY(exception_number))

// External function declarations for each exception vector
extern void EXCEPTION_ENTRY(IDT_DIVIDE_ERROR)(void);
extern void EXCEPTION_ENTRY(IDT_DEBUG)(void);
extern void EXCEPTION_ENTRY(IDT_NMI_INTERRUPT)(void);
extern void EXCEPTION_ENTRY(IDT_BREAKPOINT)(void);
extern void EXCEPTION_ENTRY(IDT_OVERFLOW)(void);
extern void EXCEPTION_ENTRY(IDT_BOUND_RANGE_EXCEEDED)(void);
extern void EXCEPTION_ENTRY(IDT_INVALID_OPCODE)(void);
extern void EXCEPTION_ENTRY(IDT_DEVICE_NOT_AVAILABLE)(void);
extern void EXCEPTION_ENTRY(IDT_DOUBLE_FAULT)(void);
extern void EXCEPTION_ENTRY(IDT_COPROCESSOR_SEGMENT_OVERRUN)(void);
extern void EXCEPTION_ENTRY(IDT_INVALID_TSS)(void);
extern void EXCEPTION_ENTRY(IDT_SEGMENT_NOT_PRESENT)(void);
extern void EXCEPTION_ENTRY(IDT_STACK_SEGMENT_FAULT)(void);
extern void EXCEPTION_ENTRY(IDT_GENERAL_PROTECTION_FAULT)(void);
extern void EXCEPTION_ENTRY(IDT_PAGE_FAULT)(void);
extern void EXCEPTION_ENTRY(IDT_RESERVED)(void);
extern void EXCEPTION_ENTRY(IDT_X87_FLOATING_POINT_ERROR)(void);
extern void EXCEPTION_ENTRY(IDT_ALIGNMENT_CHECK)(void);
extern void EXCEPTION_ENTRY(IDT_MACHINE_CHECK)(void);
extern void EXCEPTION_ENTRY(IDT_SIMD_FLOATING_POINT_ERROR)(void);
extern void EXCEPTION_ENTRY(IDT_VIRTUALIZATION_EXCEPTION)(void);
extern void EXCEPTION_ENTRY(IDT_CONTROL_PROTECTION_EXCEPTION)(void);

// External declarations for reserved exception vectors (22-31)
extern void EXCEPTION_ENTRY(IDT_EXCEPTION_RESERVED_MIN)(void);
extern void EXCEPTION_ENTRY(IDT_EXCEPTION_RESERVED_MAX)(void);

void init_idt(void);

#endif

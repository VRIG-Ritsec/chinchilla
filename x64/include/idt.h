/*
 * include/idt.h 
 * Interrupt Descriptor Table structures
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
   uint16_t offset_1;        // offset bits 0..15
   uint16_t selector;        // a code segment selector in GDT or LDT
   uint8_t  ist;             // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
   uint8_t  type_attributes; // gate type, dpl, and p fields
   uint16_t offset_2;        // offset bits 16..31
   uint32_t offset_3;        // offset bits 32..63
   uint32_t zero;            // reserved
};

// this structure is passed to the lidt instruction based off diagram here https://wiki.osdev.org/Interrupt_Descriptor_Table
struct idtr{
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

#endif

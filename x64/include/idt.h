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
#endif

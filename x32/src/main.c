#include "kernel32.h"
#include "multiboot.h"
#include "paging.h"
#include "printf.h"
#include "pic.h"
#include <stdint.h>

typedef uint8_t u8;
typedef uint32_t u32;
typedef uint64_t u64;

#define PORT 0x3f8 // COM1
#define CLEAR_SCREEN "\e[1;1H\e[2J"

struct kernel_32_info info = {0};

// note this example will always write to the top
// line of the screen
void write_string(int colour, const char *string) {
    volatile char *video = (volatile char *)0xB8000;
    while (*string != 0) {
        *video++ = *string++;
        *video++ = colour;
    }
}

extern void outb(unsigned short port, unsigned char val);
extern unsigned char inb(unsigned short port);
extern void enable_pae();
extern void enter_long_mode(void *table, struct kernel_32_info *multiboot);

extern uint64_t kernel32_reserved_start;
extern uint64_t kernel32_reserved_end;

int init_serial() {
    outb(PORT + 1, 0x00); // Disable all interrupts
    outb(PORT + 3, 0x80); // Enable DLAB (set baud rate divisor)
    outb(PORT + 0, 0x03); // Set divisor to 3 (lo byte) 38400 baud
    outb(PORT + 1, 0x00); //                  (hi byte)
    outb(PORT + 3, 0x03); // 8 bits, no parity, one stop bit
    outb(PORT + 2, 0xC7); // Enable FIFO, clear them, with 14-byte threshold
    outb(PORT + 4, 0x0B); // IRQs enabled, RTS/DSR set
    outb(PORT + 4, 0x1E); // Set in loopback mode, test the serial chip
    outb(PORT + 0, 0xAE); // Test serial chip (send byte 0xAE and check if
                          // serial returns same byte)

    // Check if serial is faulty (i.e: not same byte as sent)
    if (inb(PORT + 0) != 0xAE) {
        return 1;
    }

    // If serial is not faulty set it in normal operation mode
    // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
    outb(PORT + 4, 0x0F);

    // clears the serial output
    printf(CLEAR_SCREEN);

    return 0;
}

int main(multiboot_info_t *multiboot_info) {
    init_serial();
    printf("[+] Serial initialized\n");
    void *pgdir = init_page_table();

    info.kernel32_reserved_start = (uint32_t)&kernel32_reserved_start;
    info.kernel32_reserved_end = (uint32_t)&kernel32_reserved_end;
    info.multiboot_info = (uint32_t)multiboot_info;

    printf("[+] Attempting to enter long mode\n");
    enter_long_mode(pgdir, &info);
    // remap as despite being disabled hardware could still send a signal
    PIC_remap(0x20, 0x28);
    pic_disable();
    return 0;
}

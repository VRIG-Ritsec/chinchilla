SRC_DIR = src
OUT_DIR = build

TOOLCHAIN32 =  ../toolchain/i686/bin
TOOLCHAIN64 =  ../toolchain/x86_64/bin
CC32 = $(TOOLCHAIN32)/i686-elf-gcc
CC64 = $(TOOLCHAIN64)/x86_64-elf-gcc

CFLAGS = -g

TARGETS = main start helper printf paging buddy string idt isr
OBJECTS = $(addprefix $(OUT_DIR)/, $(addsuffix .o, $(TARGETS)))


all: kernel64

main: $(SRC_DIR)/main.c
	$(CC64) $(CFLAGS) -o $(OUT_DIR)/$@.o $< -c -I include -ffreestanding

start: $(SRC_DIR)/start.s
	nasm $(CFLAGS) -felf64 -o $(OUT_DIR)/$@.o $<

helper: $(SRC_DIR)/helper.s
	nasm -felf64 -o $(OUT_DIR)/$@.o $<

printf: $(SRC_DIR)/printf.c
	$(CC64) $(CFLAGS) -o $(OUT_DIR)/$@.o $<  -c -I include -ffreestanding
paging: $(SRC_DIR)/paging.c
	$(CC64) $(CFLAGS) -o $(OUT_DIR)/$@.o $< -c -I include -ffreestanding
buddy: $(SRC_DIR)/buddy.c
	$(CC64) $(CFLAGS) -o $(OUT_DIR)/$@.o $< -c -I include -ffreestanding 
string: $(SRC_DIR)/string.c
	$(CC64) $(CFLAGS) -o $(OUT_DIR)/$@.o $< -c -I include -ffreestanding 
idt: $(SRC_DIR)/idt.c
	$(CC64) $(CFLAGS) -o $(OUT_DIR)/$@.o $< -c -I include -ffreestanding 

isr: $(SRC_DIR)/isr.s
	nasm -felf64 -o $(OUT_DIR)/$@.o $<

kernel64: $(TARGETS) 
	$(CC64) -T linker.ld -o $(OUT_DIR)/$@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra -nostdlib -m64 -fno-pie $(OBJECTS) -lgcc


clean:
	rm -rf $(OUT_DIR)/*

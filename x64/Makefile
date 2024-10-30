SRC_DIR = src
OUT_DIR = build

TOOLCHAIN32 =  ../toolchain/i686/bin
TOOLCHAIN64 =  ../toolchain/x86_64/bin
CC32 = $(TOOLCHAIN32)/i686-elf-gcc
CC64 = $(TOOLCHAIN64)/x86_64-elf-gcc

CFLAGS = -g


all: kernel64

main64:
	$(CC64) $(CFLAGS) -o $(OUT_DIR)/main.o $(SRC_DIR)/main.c -c -I include -ffreestanding

start: $(SRC_DIR)/start.s
	nasm $(CFLAGS) -felf64 -o $(OUT_DIR)/start.o $<

helper: $(SRC_DIR)/helper.s
	nasm -felf64 -o $(OUT_DIR)/helper.o $<

printf:
	$(CC64) $(CFLAGS) -o $(OUT_DIR)/printf.o $(SRC_DIR)/printf.c -c -I include -ffreestanding

paging:
	$(CC64) $(CFLAGS) -o $(OUT_DIR)/paging.o $(SRC_DIR)/paging.c -c -I include -ffreestanding
buddy:
	$(CC64) $(CFLAGS) -o $(OUT_DIR)/buddy.o $(SRC_DIR)/buddy.c -c -I include -ffreestanding 



kernel64: helper start printf main64 paging buddy
	$(CC64) -T linker.ld -o $(OUT_DIR)/$@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra -nostdlib -m64 -fno-pie $(OUT_DIR)/start.o $(OUT_DIR)/printf.o $(OUT_DIR)/main.o $(OUT_DIR)/helper.o $(OUT_DIR)/paging.o -lgcc


clean:
	rm -rf $(OUT_DIR)/*

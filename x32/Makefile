SRC_DIR = src
OUT_DIR = build

TOOLCHAIN32 =  ../toolchain/i686/bin
TOOLCHAIN64 =  ../toolchain/x86_64/bin
CC32 = $(TOOLCHAIN32)/i686-elf-gcc
CC64 = $(TOOLCHAIN64)/x86_64-elf-gcc

all: kernel32

# this bitch is output
main:
	$(CC32) -o $(OUT_DIR)/main.o $(SRC_DIR)/main.c -c -I include -ffreestanding

printf:
	$(CC32) -o $(OUT_DIR)/printf.o $(SRC_DIR)/printf.c -c -I include -ffreestanding
paging:
	$(CC32) -o $(OUT_DIR)/paging.o $(SRC_DIR)/paging.c -c -I include -ffreestanding

#                       require files
kernel32: $(SRC_DIR)/boot.s printf paging main
	nasm -felf32 -o $(OUT_DIR)/boot.o $<
	$(CC32) -T linker.ld -o $(OUT_DIR)/$@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra -nostdlib -m64 -fno-pie $(OUT_DIR)/boot.o $(OUT_DIR)/main.o $(OUT_DIR)/printf.o $(OUT_DIR)/paging.o -lgcc

clean:
	rm -rf $(OUT_DIR)/*

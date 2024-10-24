SRC_DIR = src
OUT_DIR = build

TOOLCHAIN32 =  ../toolchain/i686/bin
TOOLCHAIN64 =  ../toolchain/x86_64/bin
CC32 = $(TOOLCHAIN32)/i686-elf-gcc
CC64 = $(TOOLCHAIN64)/x86_64-elf-gcc

all: $(OUT_DIR)/kernel64

main64:
	$(CC64) -o $(OUT_DIR)/main.o $(SRC_DIR)/main.c -c -I include -ffreestanding

start: $(SRC_DIR)/start.s
	nasm -felf64 -o $(OUT_DIR)/start.o $<

helper: $(SRC_DIR)/helper.s
	nasm -felf64 -o $(OUT_DIR)/helper.o $<

printf:
	$(CC64) -o $(OUT_DIR)/printf.o $(SRC_DIR)/printf.c -c -I include -ffreestanding


$(OUT_DIR)/kernel64: helper start printf main64
	$(CC64) -T linker.ld -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra -nostdlib -m64 -fno-pie $(OUT_DIR)/start.o $(OUT_DIR)/printf.o $(OUT_DIR)/main.o $(OUT_DIR)/helper.o -lgcc


clean:
	rm -rf $(OUT_DIR)/*

SRC_DIR = src
OUT_DIR = build

TOOLCHAIN32 =  ../toolchain/i686/bin
TOOLCHAIN64 =  ../toolchain/x86_64/bin
CC32 = $(TOOLCHAIN32)/i686-elf-gcc
CC64 = $(TOOLCHAIN64)/x86_64-elf-gcc

all: $(OUT_DIR)/kernel64

# this bitch is output
start: $(SRC_DIR)/start.s
	nasm -felf64 -o $(OUT_DIR)/start.o $<

#                       require files
$(OUT_DIR)/kernel64: start
	$(CC64) -T linker.ld -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra -nostdlib -m64 -fno-pie $(OUT_DIR)/start.o -lgcc

clean:
	rm -rf $(OUT_DIR)/*

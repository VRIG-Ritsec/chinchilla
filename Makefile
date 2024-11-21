export SHELL = /bin/sh

.SUFFIXES:
.SUFFIXES: .c .o .s


export TOOLCHAIN32=$(abspath ./toolchain/i686/bin)
export TOOLCHAIN64=$(abspath ./toolchain/x86_64/bin)
export CC32:=$(TOOLCHAIN32)/i686-elf-gcc
export CC64:=$(TOOLCHAIN64)/x86_64-elf-gcc
export ASM=nasm 


all:
	make -C x32 
	make -C x64
clean:
	make -C x32  clean
	make -C x64  clean
run:
	bash start.sh

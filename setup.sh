#!/bin/bash 


# Download the needed toolchain
mkdir toolchain && cd toolchain

mkdir i686 && cd i686
wget https://github.com/lordmilko/i686-elf-tools/releases/download/13.2.0/i686-elf-tools-linux.zip
unzip i686-elf-tools-linux.zip && rm i686-elf-tools-linux.zip

mkdir ../x86_64 && cd ../x86_64
wget https://github.com/lordmilko/i686-elf-tools/releases/download/13.2.0/x86_64-elf-tools-linux.zip
unzip x86_64-elf-tools-linux.zip && rm x86_64-elf-tools-linux.zip

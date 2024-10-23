#!/bin/bash 
qemu-system-x86_64 -cpu host -kernel ./x32/build/kernel32 -nographic -device loader,file="x64/build/kernel64" -enable-kvm -s -S 

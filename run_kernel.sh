#!/bin/bash 
qemu-system-x86_64  -m 4G -cpu host -kernel x32/build/kernel32  -device loader,file="x64/kernel64" -serial stdio -enable-kvm -nographic -monitor null -s -S 

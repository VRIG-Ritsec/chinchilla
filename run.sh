#!/bin/bash 
qemu-system-x86_64 -cpu host -kernel ./build/kernel -s -S -nographic -enable-kvm

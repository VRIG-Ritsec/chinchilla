#ifndef __KERNEL_H
#define __KERNEL_H

#include "types.h"

#define ARRAY_LEN(array) (sizeof(array) / sizeof((array[0])))

// returns container of type that holds current memeber at ptr
// Takes offset of current member in parent struct and subtracts from current
// address to get start of parent container
#define container_of(ptr, type, member)                                        \
    ((type *)((u8 *)ptr - offsetof(type, member)))

// @TODO understand dumbass macro
#define ALIGN(x, a) (x + ((1 << a) - 1) & ~(((1 << a) - 1)))

// store the start and end of kernel image so we dont' accidently free these
// pages
extern u64 kernel64_start;
extern u64 kernel64_end;

#define CONCAT(a,b) a##b
// to concat macros inside of concat
#define EXPAND_AND_CONCAT(a,b) CONCAT(a,b)

#endif

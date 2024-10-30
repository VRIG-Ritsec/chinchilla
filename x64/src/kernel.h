#ifndef __KERNEL_H
#define __KERNEL_H

#include "types.h"

// returns container of type that holds current memeber at ptr 
// Takes offset of current member in parent struct and subtracts from current address to get start of parent container
#define container_of(ptr, type, member) \
    ((type*)((u8 *)ptr - offsetof(type, member)))

#endif

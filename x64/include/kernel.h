#ifndef __KERNEL_H
#define __KERNEL_H

#include "types.h"

#define container_of(ptr, type, member) \
    ((type*)((u8 *)ptr - offsetof(type, member)))

#endif

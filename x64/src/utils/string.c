#include "string.h"

void memset(void *buf, u8 c, u64 size) {
    for (u64 i = 0; i < size; i++) {
        ((u8 *)buf)[i] = c;
    }
}

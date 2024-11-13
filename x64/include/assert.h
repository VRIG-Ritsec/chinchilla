#ifndef __ASSERT_H
#define __ASSERT_H

#define ASSERT(condition, err_msg, ...)                                        \
    ({                                                                         \
        if (condition) {                                                       \
            printf("===================================ERROR=================" \
                   "==================\nBug @ %s:%d\n%s\n",                    \
                   err_msg, __FILE__, __LINE__, ##__VA_ARGS__);                \
            __asm__("hlt");                                                    \
        }                                                                      \
    })

#endif

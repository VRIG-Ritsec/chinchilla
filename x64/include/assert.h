#ifndef __ASSERT_H
#define __ASSERT_H

#define ASSERT(condition, err_msg) ({\
if(condition){\
    printf("===================================ERROR===================================\n%s\n", err_msg);\
    __asm__("htl");\
}})\

#endif

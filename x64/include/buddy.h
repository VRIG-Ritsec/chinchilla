#ifndef __BUDDY_H
#define __BUDDY_H

#include "./list.h"
#include "./types.h"


/*#define ORDER_TO_SIZE(order) (PAGE_SIZE * 2 ** order)*/
#define ORDER_TO_SIZE (1 << (order + PAGE_SHIFT))  // same as above but uses more efficent bit shift math



// Max order of buddy sizes is 11, so max size if 0x1000 * 2 ** 11
#define MAX_ORDER 11
struct free_area{
    struct list_head orders[MAX_ORDER+1];
};

// returns a pointer to start of list_head in order
#define GET_ORDER_HEAD(order) (&(free_area.orders[order]))
#endif

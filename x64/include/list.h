#ifndef __LINK_LIST
#define __LINK_LIST


#include "kernel.h"

struct list_head{
    struct list_head* prev;
    struct list_head* next;
};

static inline void INIT_LIST_HEAD(struct list_head *head){
    head->next = head;
    head->prev = head;
}

// removes the current entry from the linked list it is part of
static inline void DELETE_LIST_HEAD(struct list_head * head){
    // @TODO Check for removing from empty list
    head->next->prev = head->prev;
    head->prev->next = head->next;

    // remove it's pointers to the rest of linked list
    INIT_LIST_HEAD(head);
}


// adds an item to the current next point of the head pointer
static inline void ADD_LIST(struct list_head * head, struct list_head * new){
    new->next = head->next;   //shift head pointer by one entry
    new->prev = head;         // inserting new after head
    head->next->prev = new;   // update value after new to point to new
    head->next = new;         // insertion of new
}


// returns entry corralated with list 
#define list_entry(ptr, type, member) (container_of(ptr, type, member)) 

// for loop to loop over items 
#define list_for_each(head, pos) for((pos) = (head)->next; pos != (head); pos = pos->next )

#endif

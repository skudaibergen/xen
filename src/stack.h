/**
 *  xen
 *
 *  Created by Sanzhar Kudaibergen on 7/12/19.
 *  Copyright © 2019 Sanzhar Kudaibergen. All rights reserved.
 */

#ifndef stack_h
#define stack_h

#include <stdint.h>     // size_t comes from here
#include <stdlib.h>     // free() comes from here


typedef struct stack Stack;

typedef struct node
{
    void *data;
    struct node *next;
} Node;

void stack_init(Stack **out);
void stack_push(Stack *stack, void *el);
void *stack_pop(Stack *stack);
size_t stack_size (Stack *stack);

#endif

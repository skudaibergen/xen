/**
 *  xen
 *
 *  Created by Sanzhar Kudaibergen on 7/12/19.
 *  Copyright © 2019 Sanzhar Kudaibergen. All rights reserved.
 */

#include "stack.h"


struct stack
{
    size_t size;
    Node *head;
    
    void *(*mem_alloc) (size_t size);
    void (*mem_free) (void *block);
};

void stack_init(Stack **out)
{
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    stack->size = 0;
    *out = stack;
}

void stack_push(Stack *stack, void *el)
{
    Node *node = (Node *) malloc(sizeof(Node));
    
    node->next = stack->head;
    stack->head = node;
    
    node->data = el;
    stack->size++;
}

void *stack_pop(Stack *stack)
{
    Node *rmv = stack->head;
    void *data = stack->head->data;
    
    stack->head = rmv->next;
    free(rmv);
    stack->size--;
    
    return data;
}

size_t stack_size(Stack *stack)
{
    return stack->size;
}

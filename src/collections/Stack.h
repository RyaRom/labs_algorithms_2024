//
// Created by locadm on 9/11/2024.
//

#ifndef STACK_H
#define STACK_H

typedef struct StackNode {
    void *value;
    struct StackNode *next;
} StackNode;

typedef struct Stack {
    StackNode *top;
    int size;
} Stack;

Stack *newStack();

void stack_push(Stack *stack, void *data);

void *stack_pop(Stack *stack);

void *stack_peek(const Stack *stack);

int stack_is_empty(const Stack *stack);

void stack_free(Stack *stack);

#endif //STACK_H

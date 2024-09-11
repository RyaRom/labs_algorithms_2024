#include <stdio.h>

#include "collections/Stack.h"

void lab3() {
    Stack *stack = newStack();
    int a = 10;
    stack_push(stack, &a);
    printf("%d", *(int *) stack_pop(stack));
}

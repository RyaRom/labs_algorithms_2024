//
// Created by locadm on 9/11/2024.
//

#include "Stack.h"

#include <stdio.h>
#include <stdlib.h>

#include "lab3structs/cpuSim.h"


Stack *newStack() {
    Stack *stack = malloc(sizeof(Stack));
    if (stack == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    stack->size = 0;
    stack->top = NULL;
    return stack;
}

void stack_push(Stack *stack, void *data) {
    StackNode *newNode = malloc(sizeof(StackNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    newNode->value = data;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;
}

void *stack_pop(Stack *stack) {
    if (stack_is_empty(stack))return NULL;
    StackNode *top = stack->top;
    void *val = top->value;
    stack->top = top->next;
    free(top);
    stack->size--;
    return val;
}

void *stack_peek(const Stack *stack) {
    if (stack_is_empty(stack))return NULL;
    return stack->top->value;
}

int stack_is_empty(const Stack *stack) {
    if (stack == NULL || stack->size == 0) return 1;
    return 0;
}

void stack_free(Stack *stack) {
    while (!stack_is_empty(stack)) {
        stack_pop(stack);
    }
    free(stack);
}

void stack_display_tasks(const Stack *stack) {
    if (stack_is_empty(stack)) return;
    const StackNode *current = stack->top;
    while (current != NULL) {
        const Task *task = current->value;
        printf("Task ID: %d, Task time: %d, Duration time: %d\n", task->taskId, task->taskTime, task->durationTime);
        current = current->next;
    }
}

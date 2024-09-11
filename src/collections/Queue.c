//
// Created by locadm on 9/11/2024.
//

#include "Queue.h"

#include <stdio.h>
#include <stdlib.h>

#include "Stack.h"
#include "lab3structs/cpuSim.h"

Queue *newQueue() {
    Queue *queue = malloc(sizeof(Queue));
    if (queue == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    queue->top = NULL;
    queue->bottom = NULL;
    queue->size = 0;
    return queue;
}

void queue_enqueue(Queue *queue, void *value) {
    QueueNode *node = malloc(sizeof(QueueNode));
    node->value = value;
    node->next = NULL;
    if (queue->bottom == NULL) {
        queue->bottom = node;
        queue->top = node;
    } else {
        queue->bottom->next = node;
        queue->bottom = node;
    }
    queue->size++;
}

void *queue_dequeue(Queue *queue) {
    if (queue_is_empty(queue)) return NULL;

    QueueNode *top = queue->top;
    void *value = top->value;
    QueueNode *newTop = top->next;

    if (newTop == NULL) {
        queue->bottom = NULL;
    }
    queue->top = newTop;


    free(top);
    queue->size--;
    return value;
}

void *queue_peek(const Queue *queue) {
    if (queue_is_empty(queue)) return NULL;
    return queue->top->value;
}

void queue_free(Queue *queue) {
    while (!queue_is_empty(queue)) {
        queue_dequeue(queue);
    }
    free(queue);
}

int queue_is_empty(const Queue *queue) {
    if (queue == NULL || queue->size == 0) return 1;
    return 0;
}

void queue_display_tasks(const Queue *queue) {
    if (queue_is_empty(queue)) return;
    const QueueNode *current = queue->top;
    while (current != NULL) {
        const Task *task = current->value;
        printf("Task ID: %d, Task time: %d, Duration time: %d\n", task->taskId, task->taskTime, task->durationTime);
        current = current->next;
    }
}

//
// Created by locadm on 9/11/2024.
//

#ifndef QUEUE_H
#define QUEUE_H

typedef struct QueueNode {
    void *value;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue {
    QueueNode *top;
    QueueNode *bottom;
    int size;
} Queue;

Queue *newQueue();

void queue_enqueue(Queue *queue, void *value);

void *queue_dequeue(Queue *queue);

void *queue_peek(const Queue *queue);

void queue_free(Queue *queue);

int queue_is_empty(const Queue *queue);

void queue_display_tasks(const Queue *queue);

#endif //QUEUE_H

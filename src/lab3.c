#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "collections/Queue.h"
#include "collections/Stack.h"
#include "lab3structs/cpuSim.h"
#include "utils/Random.h"

void generateTasks(Queue *taskQueue, int count);

void lab3() {
    CPU *cpu1 = newCpu();
    CPU *cpu2 = newCpu();
    Stack *taskStack = newStack();
    Queue *taskQueue = newQueue();
    generateTasks(taskQueue, 10);

    printf("Task queue:\n");
    queue_display_tasks(taskQueue);
}

void generateTasks(Queue *taskQueue, const int count) {
    random_init();
    for (int i = 1; i <= count; ++i) {
        const int duration = random_int(10, 1);
        Task *task = malloc(sizeof(Task));
        task->durationTime = duration;
        task->taskId = i;
        task->taskTime = 0;
        queue_enqueue(taskQueue, task);
    }
}

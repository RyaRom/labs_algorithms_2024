#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "collections/Queue.h"
#include "collections/Stack.h"
#include "lab3structs/cpuSim.h"
#include "utils/Random.h"

void generateTasks(Queue *taskQueue, int count);

void print_current_cycle(const Queue *taskQueue, const Stack *taskStack, const CPU *cpu1, const CPU *cpu2, int cycle,
                         const Queue *finished);

void simulateCpu(Queue *taskQueue, Stack *taskStack, CPU *cpu1, CPU *cpu2);

void lab3() {
    CPU *cpu1 = newCpu();
    CPU *cpu2 = newCpu();
    Stack *taskStack = newStack();
    Queue *taskQueue = newQueue();
    generateTasks(taskQueue, 10);

    simulateCpu(taskQueue, taskStack, cpu1, cpu2);
}

void generateTasks(Queue *taskQueue, const int count) {
    random_init();
    for (int i = 1; i <= count; ++i) {
        const int duration = random_int(5, 1);
        Task *task = malloc(sizeof(Task));
        task->durationTime = duration;
        task->taskId = i;
        task->taskTime = 0;
        queue_enqueue(taskQueue, task);
    }
}

void simulateCpu(Queue *taskQueue, Stack *taskStack, CPU *cpu1, CPU *cpu2) {
    Queue *finished = newQueue();
    int cycle = 1;
    while (!queue_is_empty(taskQueue)) {
        print_current_cycle(taskQueue, taskStack, cpu1, cpu2, cycle, finished);
        //push new task to P1 if it's empty
        Task *taskFromCpu1 = newTask();
        const int append_to_cpu1 = cpu_cycle(taskFromCpu1, cycle, cpu1);
        if (append_to_cpu1 == 1) {
            Task *task = queue_dequeue(taskQueue);
            task->taskTime = cycle;
            cpu1->currentTask = task;
            stack_push(taskStack, taskFromCpu1);
        } else if (append_to_cpu1 == 2) {
            Task *task = queue_dequeue(taskQueue);
            task->taskTime = cycle;
            cpu1->currentTask = task;
        }

        //push new task to P2 if it's empty
        Task *output = newTask();
        const int append_to_cpu2 = cpu_cycle(output, cycle, cpu2);
        if (stack_is_empty(taskStack) && append_to_cpu2 == 1) {
            queue_enqueue(finished, output);
        } else if (!stack_is_empty(taskStack) && append_to_cpu2 == 1) {
            Task *task = stack_pop(taskStack);
            task->taskTime = cycle;
            cpu2->currentTask = task;
            queue_enqueue(finished, output);
        } else if (!stack_is_empty(taskStack) && append_to_cpu2 == 2) {
            Task *task = stack_pop(taskStack);
            task->taskTime = cycle;
            cpu2->currentTask = task;
        }

        cycle++;
    }
    print_current_cycle(taskQueue, taskStack, cpu1, cpu2, cycle, finished);
}

void print_current_cycle(const Queue *taskQueue, const Stack *taskStack, const CPU *cpu1, const CPU *cpu2,
                         const int cycle, const Queue *finished) {
    printf("Cycle: %d\n", cycle);
    printf("Task queue:\n");
    queue_display_tasks(taskQueue);
    printf("CPU 1:\n");
    cpu_display(cpu1);
    printf("CPU 2:\n");
    cpu_display(cpu2);
    printf("Task stack: \n");
    stack_display_tasks(taskStack);
    printf("finished: \n\n\n");
    queue_display_tasks(finished);

    Sleep(2000);
}

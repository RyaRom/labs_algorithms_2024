//
// Created by locadm on 9/11/2024.
//

#include "cpuSim.h"

#include <stdio.h>
#include <stdlib.h>

CPU *newCpu() {
    CPU *cpu = malloc(sizeof(CPU));
    if (cpu == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    cpu->currentTask = NULL;
    return cpu;
}

Task *newTask() {
    Task *task = malloc(sizeof(Task));
    if (task == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    return task;
}

int cpu_cycle(Task *task, const int currentCycle, CPU *cpu) {
    const Task *current = cpu->currentTask;

    if (current == NULL) {
        return 2;
    }

    if (currentCycle - current->taskTime >= current->durationTime) {
        *task = *current;
        cpu->currentTask = NULL;
        return 1;
    }
    return 0;
}

void cpu_display(const CPU *cpu) {
    if (cpu->currentTask == NULL) {
        printf("CPU: No task\n");
        return;
    }
    printf("CPU: Task ID: %d, Task time: %d, Duration time: %d\n", cpu->currentTask->taskId,
           cpu->currentTask->taskTime, cpu->currentTask->durationTime);
}

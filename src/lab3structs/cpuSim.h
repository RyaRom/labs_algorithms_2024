//
// Created by locadm on 9/11/2024.
//

#ifndef CPUSIM_H
#define CPUSIM_H
#include <stdint.h>

typedef struct Task {
    uint16_t taskId;
    uint16_t taskTime;
    uint16_t durationTime;
} Task;

typedef struct CPU {
    Task *currentTask;
} CPU;

CPU *newCpu();

int cpuCycle(Task *task, int currentCycle);
#endif //CPUSIM_H
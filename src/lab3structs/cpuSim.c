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

int cpuCycle(Task *task, int currentCycle) {
}

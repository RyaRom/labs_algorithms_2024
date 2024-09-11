//
// Created by locadm on 9/11/2024.
//

#include "Random.h"

#include <stdlib.h>
#include <time.h>

int random_int(const int upperBound, const int lowerBound) {
    return (rand() % (upperBound + 1 - lowerBound)) + lowerBound;
}

void random_init() {
    srand(time(NULL));
}

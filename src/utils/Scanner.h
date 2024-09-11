//
// Created by locadm on 9/11/2024.
//

#ifndef SCANNER_H
#define SCANNER_H
#include <stdio.h>

typedef struct Scanner Scanner;

void read_int_sequence(void *collection, FILE *stream, int bufferSize);

char* read_line(FILE *stream, int bufferSize);

#endif //SCANNER_H

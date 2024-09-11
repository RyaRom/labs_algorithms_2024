//
// Created by locadm on 9/11/2024.
//

#include "Scanner.h"

#include <stdlib.h>
#include <string.h>

int is_integer_internal(char *str) {
};


void read_int_sequence(void *collection, FILE *stream, const int bufferSize) {
    char input[50];

    while (fgets(input, sizeof(input), stream) != NULL) {
        printf("Enter sequence element (enter \"exit\" to exit program):\n");

        input[strcspn(input, "\n")] = 0;
    }
}

char *read_line(FILE *stream, const int bufferSize) {
    char *input = malloc(bufferSize * sizeof(char));
    if (input == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return NULL;
    }
    if (fgets(input, bufferSize, stream) != NULL) {
        input[strcspn(input, "\n")] = '\0';
    } else {
        free(input);
        return NULL;
    }
    return input;
}

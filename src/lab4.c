#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "collections/HashTable.h"
#define filePath "C:\\Users\\locadm\\CLionProjects\\Suai_labs_algorithms_2024\\src\\resources\\table.csv"

void generate_random_string(char *str, size_t length);

int _KR_v2_hash(const char *s);

void check_collisions();

uint32_t _DJB2_hash(const char *s);

void lab4() {
    check_collisions();

    HashTable *table = new_hash_table();
    hashtable_put(table);
}

void check_collisions() {
    FILE *file = fopen(filePath, "w");
    if (!file) {
        printf("Failed to create file!\n");
    }

    srand(time(NULL));
    fprintf(file, "Hash,Collisions\n");
    const int size = 1000;
    uint32_t *collisions = calloc(size, sizeof(int));
    for (int i = 0; i < 100000; i++) {
        char random_string[11];
        generate_random_string(random_string, 10);
        const uint32_t hash = _KR_v2_hash(random_string) % size;
        collisions[hash]++;
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%d,%d\n", i, collisions[i]);
    }

    fclose(file);

    printf("CSV file generating...\n");
    free(collisions);
}

void generate_random_string(char *str, size_t length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (size_t i = 0; i < length; i++) {
        const int random_index = rand() % (sizeof(charset) - 1);
        str[i] = charset[random_index];
    }
    str[length] = '\0';
}

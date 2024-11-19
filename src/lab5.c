#include <stdbool.h>
#include <stdio.h>
#include <windows.h>
typedef int type;

void comb_sort(type *arr, const int size);

void swap(type *arr, int i, int j);

void print_arr(const type *arr, const int size);

void lab5() {
    int size = 10;
    type *arr = calloc(size, sizeof(type));
    for (int i = 0; i < size; i++) {
        arr[i] = size - i;
    }
    comb_sort(arr, size);
    print_arr(arr, size);
}

void print_arr(const type *arr, const int size) {
    for (int i = 0; i < size; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }
}

void comb_sort(type *arr, const int size) {
    int gap = size - 1;
    boolean wasSwapped = false;
    while (true) {
        wasSwapped = false;
        int current = 0;
        while (current + gap < size) {
            if (arr[current] > arr[current + gap]) {
                wasSwapped = true;
                swap(arr, current, current + gap);
            }
            current += gap;
        }
        gap = max(1, gap / 1.3);
        if (wasSwapped == false && gap == 1) {
            break;
        }
    }
}

void swap(type *arr, int i, int j) {
    const int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

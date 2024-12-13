#include <pthread_time.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>
typedef int type;

void comb_sort(type *arr, int size);

type *create_random_array(int size, int min, int max);

type *create_sorted_array(int size);

type *create_unsorted_array(int size);

void swap(type *arr, int i, int j);

void print_arr(const type *arr, int size);

void remove_elem(int index, type **arr, int *size);

void add_elem(type val, type **arr, int *size);

long long current_time_milliseconds();

type get_by_index(int i, type *arr);

int get_by_val(type val, type *arr, int size);

boolean compare(type first, type second);

void test_array_sort(int size);

int compares = 0;
int swaps = 0;

void test_array_sort(const int size) {
    type *arr_random = create_random_array(size, 0, size - 1);
    long long start = current_time_milliseconds();
    comb_sort(arr_random, size);
    long long end = current_time_milliseconds();
    long long time_for_random = end - start;

    type *arr_sorted = create_sorted_array(size);
    start = current_time_milliseconds();
    comb_sort(arr_sorted, size);
    end = current_time_milliseconds();
    long long time_for_sorted = end - start;

    type *arr_unsorted = create_unsorted_array(size);
    start = current_time_milliseconds();
    comb_sort(arr_unsorted, size);
    end = current_time_milliseconds();
    long long time_for_unsorted = end - start;

    free(arr_random);
    free(arr_sorted);
    free(arr_unsorted);
    printf("\n Time: %lld ms for %d elem in random array\n", time_for_random, size);
    printf("\n Time: %lld ms for %d elem in sorted array\n", time_for_sorted, size);
    printf("\n Time: %lld ms for %d elem in reversed sorted array\n", time_for_unsorted, size);
}

type *create_random_array(int size, int min, int max) {
    type *array = calloc(size, sizeof(type));
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        array[i] = rand() % (max - min + 1) + min;
    }

    return array;
}

type *create_sorted_array(int size) {
    type *arr = calloc(size, sizeof(type));
    for (int i = 0; i < size; ++i) {
        arr[i] = i;
    }
    return arr;
}

type *create_unsorted_array(int size) {
    type *arr = calloc(size, sizeof(type));
    for (int i = 0; i < size; ++i) {
        arr[i] = size - i - 1;
    }
    return arr;
}


void lab5() {
    test_array_sort(1e4);

    printf("\n Swaps : %d", swaps);
    printf("\n Compares : %d", compares);
}

void print_arr(const type *arr, const int size) {
    for (int i = 0; i < size; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }
}

type get_by_index(int i, type *arr) {
    return arr[i];
}

int get_by_val(type val, type *arr, int size) {
    comb_sort(arr, size);
    int left = 0;
    int right = size - 1;
    while (right >= left) {
        int mid = (left + right) >> 1;
        if (arr[mid] == val) {
            return mid;
        }
        if (arr[mid] < val) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

void add_elem(type val, type **arr, int *size) {
    (*size)++;
    *arr = realloc(*arr, *size * sizeof(type));
    (*arr)[(*size) - 1] = val;

    comb_sort(*arr, *size);
}

void remove_elem(int index, type **arr, int *size) {
    for (int i = index; i < *size - 1; i++) {
        (*arr)[i] = (*arr)[i + 1];
    }
    (*size)--;
    *arr = realloc(*arr, (*size) * sizeof(type));

    comb_sort(*arr, *size);
}

void comb_sort(type *arr, const int size) {
    int gap = size - 1;
    boolean wasSwapped = false;
    while (true) {
        wasSwapped = false;
        int current = 0;
        while (compare(current + gap, size)) {
            if (compare(arr[current + gap], arr[current])) {
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
    swaps++;
    const int temp = arr[i];

    arr[i] = arr[j];
    arr[j] = temp;
}

boolean compare(const type first, const type second) {
    compares++;
    return first < second;
}

long long current_time_milliseconds() {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return ts.tv_sec * 1000 + (ts.tv_nsec) / 1000000;
}

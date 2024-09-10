#include <stdio.h>
#include <stdlib.h>

void matrix_columns_sum(int matrix[][3], int *sums, const int rows, const int cols);

int main(void) {
    const int rows = 4;
    const int cols = 3;
    int matrix[4][3] = {
        {1, 2, 3},
        {1, 2, 3},
        {1, 2, 3},
        {1, 2, 3},
    };

    int *row_sum = malloc(sizeof(int) * cols);
    matrix_columns_sum(matrix, row_sum, rows, cols);

    for (int i = 0; i < cols; i++) {
        printf("%d ", row_sum[i]);
    }
    free(row_sum);
}

void matrix_columns_sum(int matrix[][3], int *sums, const int rows, const int cols) {
    for (int j = 0; j < cols; j++) {
        sums[j] = 0;
        for (int i = 0; i < rows; i++) {
            sums[j] += matrix[i][j];
        }
    }
}

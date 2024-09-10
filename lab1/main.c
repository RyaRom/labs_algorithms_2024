#include <stdio.h>
#include <stdlib.h>

void read_matrix(int **matrix, int cols, int rows);

void matrix_columns_sum(int **matrix, int *sums, int rows, int cols);

void print_array(const int *array, int size);

int main(void) {
    int rows, cols;

    printf("Enter number of rows: \n");
    scanf("%d", &rows);
    printf("Enter number of columns: \n");
    scanf("%d", &cols);

    int **matrix = malloc(rows * sizeof(int *));
    int *row_sum = malloc(sizeof(int) * cols);
    if (matrix == NULL || row_sum == NULL) {
        perror("Failed to allocate memory");
        return 1;
    }

    read_matrix(matrix, cols, rows);

    matrix_columns_sum(matrix, row_sum, rows, cols);

    print_array(row_sum, cols);

    free(row_sum);
    free(matrix);
}

void print_array(const int *array, const int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
}

void read_matrix(int **matrix, const int cols, const int rows) {
    printf("Enter the matrix elements:\n");
    for (int i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++) {
            printf("Element [%d][%d]: \n", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }
}

void matrix_columns_sum(int **matrix, int *sums, const int rows, const int cols) {
    for (int j = 0; j < cols; j++) {
        sums[j] = 0;
        for (int i = 0; i < rows; i++) {
            sums[j] += matrix[i][j];
        }
    }
}

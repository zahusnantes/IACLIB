#include <stdio.h>
#include <stdlib.h>

#include "../inc/tools.h"
#include <../inc/images.h>

#include <stdio.h>
#include <stdlib.h>

#define MATRIX_SIZE 3
#define KERNEL_SIZE 2

// Function to print a matrix
void printMatrix(float *matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%f ", matrix[i * cols + j]);
        }
        printf("\n");
    }
}

int main() {
    float matrix[MATRIX_SIZE * MATRIX_SIZE] = {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    float kernel[KERNEL_SIZE * KERNEL_SIZE] = {
        0.5, 1.0,
        -0.5, 2.0
    };

    printMatrix(matrix, MATRIX_SIZE, MATRIX_SIZE);

    printMatrix(kernel, KERNEL_SIZE, KERNEL_SIZE);

    return 0;
}


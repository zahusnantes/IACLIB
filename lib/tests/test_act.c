#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../inc/activation.h"

void print_array(const char *label, double *arr, int length) {
    printf("%s: ", label);
    for (int i = 0; i < length; ++i) {
        printf("%.4f ", arr[i]);
    }
    printf("\n");
}

int main() {
    // Test array
    double values[] = {-2.0, -1.0, 0.0, 1.0, 2.0};
    int length = sizeof(values) / sizeof(values[0]);

    // Test ReLU
    print_array("Original", values, length);
    relu(values, length);
    print_array("ReLU", values, length);

    // Reset array for Sigmoid test
    for (int i = 0; i < length; ++i) {
        values[i] = i - 2.0; // Some different values for sigmoid
    }

    // Test Sigmoid
    print_array("Original", values, length);
    sigmoid(values, length);
    print_array("Sigmoid", values, length);

    // Reset array for Softmax test
    for (int i = 0; i < length; ++i) {
        values[i] = i - 2.0; // Some different values for softmax
    }

    // Test Softmax
    double softmax_output[length];
    print_array("Original", values, length);
    softmax(values, length, softmax_output);
    print_array("Softmax", softmax_output, length);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

#include "../inc/tools.h"
#include "../inc/images.h"
#include "../inc/conv.h"

#define MATRIX_SIZE 3
#define KERNEL_SIZE 2

void print3DMatrix(DATA3D *matrix) {
    for (int d = 0; d < matrix->shape.depth; ++d) {
        printf("Depth %d:\n", d);
        for (int i = 0; i < matrix->shape.width; ++i) {
            for (int j = 0; j < matrix->shape.height; ++j) {
                printf("%5.0f ", matrix->raw_data[d * matrix->shape.width * matrix->shape.height + i * matrix->shape.height + j]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

int main() {
// Create a 3D matrix with 2 channels (3x3x2)
    DATA3D matrix;
    matrix.shape.width = 3;
    matrix.shape.height = 3;
    matrix.shape.depth = 1;
    matrix.raw_data = malloc(matrix.shape.width * matrix.shape.height * matrix.shape.depth * sizeof(DATA_TYPE));

    // Initialize the matrix with some values
    for (int i = 0; i < matrix.shape.width * matrix.shape.height * matrix.shape.depth; ++i) {
        matrix.raw_data[i] = i;
    }

    // Create a linearized version of the matrix
    matrix.linearized_data.shape.length = matrix.shape.width * matrix.shape.height * matrix.shape.depth;
    matrix.linearized_data.raw_data = malloc(matrix.linearized_data.shape.length * sizeof(DATA_TYPE));

    // Copy data from the 3D matrix to the linearized version
    for (int i = 0; i < matrix.linearized_data.shape.length; ++i) {
        matrix.linearized_data.raw_data[i] = matrix.raw_data[i];
    }

    // printf("Non-Linearized Matrix:\n");
    // print3DMatrix(&matrix);

    // // Print the linearized version
    // printf("Linearized Matrix:\n");
    // for (int i = 0; i < matrix.linearized_data.shape.length; ++i) {
    //     printf("%f ", matrix.linearized_data.raw_data[i]);
    // }
    // printf("\n\n");

    DATA3D kernel;
    kernel.shape.width = 2;
    kernel.shape.height = 2;
    kernel.shape.depth = 2;
    kernel.raw_data = malloc(kernel.shape.width * kernel.shape.height * kernel.shape.depth * sizeof(DATA_TYPE));

    // Initialize the kernel with some values (you can replace this with your actual data)
    for (int i = 0; i < kernel.shape.width * kernel.shape.height * kernel.shape.depth; ++i) {
        kernel.raw_data[i] = i;
    }

    // Create a linearized version of the kernel
    kernel.linearized_data.shape.length = kernel.shape.width * kernel.shape.height * kernel.shape.depth;
    kernel.linearized_data.raw_data = malloc(kernel.linearized_data.shape.length * sizeof(DATA_TYPE));

    // Copy data from the 3D kernel to the linearized version
    for (int i = 0; i < kernel.linearized_data.shape.length; ++i) {
        kernel.linearized_data.raw_data[i] = kernel.raw_data[i];
    }

    // printf("Non-Linearized Kernel:\n");
    // print3DMatrix(&kernel);

    // // Print the linearized version
    // printf("\nLinearized Kernel:\n");
    // for (int i = 0; i < kernel.linearized_data.shape.length; ++i) {
    //     printf("%f ", kernel.linearized_data.raw_data[i]);
    // }
    // printf("\n");

    // Create linearized versions of matrix and kernel
    DATA1D linearized_matrix, linearized_kernel;
    initialize_DATA1D(&linearized_matrix, matrix.linearized_data.shape.length);
    initialize_DATA1D(&linearized_kernel, kernel.linearized_data.shape.length);

    // Copy data from the linearized matrix and kernel
    for (int i = 0; i < linearized_matrix.shape.length; ++i) {
        linearized_matrix.raw_data[i] = matrix.linearized_data.raw_data[i];
    }

    for (int i = 0; i < linearized_kernel.shape.length; ++i) {
        linearized_kernel.raw_data[i] = kernel.linearized_data.raw_data[i];
    }

    int nb_classes = 2;

    CNN *cnn = read_model("../model/MNIST/model_cnn.dat", matrix.shape.height, kernel.shape.width, nb_classes);

    Layer *conv_layer = find_layer(cnn, "conv1");

    int input_height = matrix.shape.height;
    int input_width = matrix.shape.width;
    int kernel_size = conv_layer->params.kernels.shape.height;
    int padding = conv_layer->params.kernels.padding;
    int stride = conv_layer->params.kernels.stride;
    int output_height = (input_height - kernel_size + 2 * padding) / stride + 1;
    int output_width = (input_width - kernel_size + 2 * padding) / stride + 1;
    int output_depth = conv_layer->params.kernels.shape.depth;

    int output_size = output_width * output_height * output_depth;

    printf("output_size = %d\n", output_size);
    DATA1D output_data;
    initialize_DATA1D(&output_data, output_size);

    bool success = conv(conv_layer, &linearized_matrix, &linearized_kernel, &output_data, input_height, input_width);

    // Print the output
    printf("\nConvolution Output:\n");
    for (int i = 0; i < output_data.shape.length; ++i) {
        printf("%f ", output_data.raw_data[i]);
    }
    printf("\n");

    // Free allocated memory
    free(matrix.raw_data);
    free(matrix.linearized_data.raw_data);
    free(kernel.raw_data);
    free(kernel.linearized_data.raw_data);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

#include "../inc/tools.h"
#include "../inc/images.h"
#include "../inc/conv.h"
#include "../inc/pooling.h"

#define MATRIX_SIZE 3
#define KERNEL_SIZE 2

int main() {
// Create a 3D matrix with 2 channels (3x3x2)
    DATA3D matrix;
    matrix.shape.width = 3;
    matrix.shape.height = 3;
    matrix.shape.depth = 1;
    initialize_DATA3D(&matrix, matrix.shape.height, matrix.shape.width, matrix.shape.depth);
    initialize_DATA1D(&matrix.linearized_data, matrix.shape.width * matrix.shape.height * matrix.shape.depth);
    // Initialize the 3D matrix
    for (int i = 0; i < matrix.shape.width * matrix.shape.height * matrix.shape.depth; ++i) {
        matrix.raw_data[i] = i;
    }
    // Copy data from the 3D matrix to the linearized version
    for (int i = 0; i < matrix.linearized_data.shape.length; ++i) {
        matrix.linearized_data.raw_data[i] = matrix.raw_data[i];
    }

    DATA3D kernel;
    kernel.shape.width = 2;
    kernel.shape.height = 2;
    kernel.shape.depth = 2;
    initialize_DATA3D(&kernel, kernel.shape.height, kernel.shape.width, kernel.shape.depth);
    initialize_DATA1D(&kernel.linearized_data, kernel.shape.width * kernel.shape.height * kernel.shape.depth);
    // Initialize the 3D kernel 
    for (int i = 0; i < kernel.shape.width * kernel.shape.height * kernel.shape.depth; ++i) {
        kernel.raw_data[i] = i;
    }
    // Copy data from the 3D kernel to the linearized version
    for (int i = 0; i < kernel.linearized_data.shape.length; ++i) {
        kernel.linearized_data.raw_data[i] = kernel.raw_data[i];
    }

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
    Layer *pooling_layer = find_layer(cnn, "pool1");

    int input_height = matrix.shape.height;
    int input_width = matrix.shape.width;
    int kernel_size = conv_layer->params.kernels.shape.height;
    int padding = conv_layer->params.kernels.padding;
    int stride = conv_layer->params.kernels.stride;
    int conv_output_height = (input_height - kernel_size + 2 * padding) / stride + 1;
    int conv_output_width = (input_width - kernel_size + 2 * padding) / stride + 1;
    int conv_output_depth = conv_layer->params.kernels.shape.depth;
    int conv_output_size = conv_output_width * conv_output_height * conv_output_depth;
    DATA1D conv_output_data;
    initialize_DATA1D(&conv_output_data, conv_output_size);

    if (conv(conv_layer, &linearized_matrix, &linearized_kernel, &conv_output_data, input_height, input_width)) {
        printf("Convolution successful!\n");
        printf("Convolution Output:\n");
        for (int i = 0; i < conv_output_data.shape.length; ++i) {
            printf("%f ", conv_output_data.raw_data[i]);
        }
        printf("\n");
    } else {
        fprintf(stderr, "Convolution failed!\n");
        return EXIT_FAILURE;
    }

    int pool_size = pooling_layer->params.pool.shape.height;
    int pool_stride = pooling_layer->params.pool.stride;
    int pool_padding = pooling_layer->params.pool.padding;
    PoolingType pool_type = pooling_layer->params.pool.type;

    printf("Pooling Layer Parameters:\n");
    printf("  Pool Size: %d\n", pooling_layer->params.pool.shape.height);
    printf("  Pool Stride: %d\n", pooling_layer->params.pool.stride);
    printf("  Pool Padding: %d\n", pooling_layer->params.pool.padding);
    printf("  Pool Type: %d\n", pooling_layer->params.pool.type);
    printf("Pooling Type: %s\n", poolingType_to_str(pool_type));

    // int pool_output_width = conv_output_width / 
    // int pool_output_size = pool_output_width * pool_output_height * pool_output_depth;
    // DATA1D pool_output_data;
    // initialize_DATA1D(&pool_output_data, pool_output_size);


    // if (pooling(pooling_layer, &linearized_matrix, &pool_output_data)) {
    //     printf("Pooling successful!\n");
    //     printf("Pooling Output:\n");
    //     for (int i = 0; i < pool_output_data.shape.length; ++i) {
    //         printf("%f ", pool_output_data.raw_data[i]);
    //     }
    //     printf("\n");
    // } else {
    //     fprintf(stderr, "Pooling failed!\n");
    //     return EXIT_FAILURE;
    // }

    free(matrix.raw_data);
    free(matrix.linearized_data.raw_data);
    free(kernel.raw_data);
    free(kernel.linearized_data.raw_data);

    return 0;
}
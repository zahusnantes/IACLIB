#include <stdio.h>
#include <stdlib.h>

#include "../inc/tools.h"
#include "../inc/images.h"
#include "../inc/conv.h"
#include "../inc/pooling.h"

int main() {
// Create a 3D matrix with 2 channels (3x3x2)
    DATA3D matrix;
    matrix.shape.width = 3;
    matrix.shape.height = 3;
    matrix.shape.depth = 1;
    initialize_DATA3D(&matrix, matrix.shape.height, matrix.shape.width, matrix.shape.depth);
    DATA1D linearized_matrix;
    initialize_DATA1D(&matrix.linearized_data, matrix.shape.width * matrix.shape.height * matrix.shape.depth);
    for (int i = 0; i < matrix.shape.width * matrix.shape.height * matrix.shape.depth; ++i) {
        matrix.raw_data[i] = i;
    }
    for (int i = 0; i < matrix.linearized_data.shape.length; ++i) {
        matrix.linearized_data.raw_data[i] = matrix.raw_data[i];
    }

    DATA3D kernel;
    kernel.shape.width = 2;
    kernel.shape.height = 2;
    kernel.shape.depth = 2;
    initialize_DATA3D(&kernel, kernel.shape.height, kernel.shape.width, kernel.shape.depth);
    DATA1D linearized_kernel;
    initialize_DATA1D(&kernel.linearized_data, kernel.shape.width * kernel.shape.height * kernel.shape.depth);
    for (int i = 0; i < kernel.shape.width * kernel.shape.height * kernel.shape.depth; ++i) {
        kernel.raw_data[i] = i;
    }
    for (int i = 0; i < kernel.linearized_data.shape.length; ++i) {
        kernel.linearized_data.raw_data[i] = kernel.raw_data[i];
    }

    int nb_classes = 2;

    CNN *cnn = read_model("../model/MNIST/model_cnn.dat", matrix.shape.height, matrix.shape.width, matrix.shape.depth, nb_classes);
    Layer *conv_layer = find_layer(cnn, "conv1");
    Layer *pooling_layer = find_layer(cnn, "pool1");

    DATA3D conv_output_data;
    conv_output_data.shape.width = conv_layer->data.shape.width;
    conv_output_data.shape.height = conv_layer->data.shape.height;
    conv_output_data.shape.depth = conv_layer->data.shape.depth;
    printf("Conv Output Data Width: %d\n", conv_output_data.shape.width);
    printf("Conv Output Data Height: %d\n", conv_output_data.shape.height);
    printf("Conv Output Data Depth: %d\n", conv_output_data.shape.depth); // it's wrong, check

    int conv_output_size = conv_output_data.shape.width * conv_output_data.shape.height * conv_output_data.shape.depth;
    printf("Conv Output Data Size: %d\n", conv_output_size);
    initialize_DATA3D(&conv_output_data, conv_output_data.shape.height, conv_output_data.shape.width, conv_output_data.shape.depth);

    if (conv(conv_layer, &matrix, &kernel, &conv_output_data)) {
        printf("Convolution Output:\n");
        for (int i = 0; i < conv_output_size; ++i) {
            printf("%f ", conv_output_data.raw_data[i]);
        }
        printf("\n");
    } else {
        fprintf(stderr, "Convolution failed!\n");
        return EXIT_FAILURE;
    }

    PoolingType pool_type = pooling_layer->params.pool.type;
    printf("Pooling type = %s\n", poolingType_to_str(pool_type));

    int pool_output_width = pooling_layer->params.pool.shape.height;
    int pool_output_height = pooling_layer->params.pool.shape.height;
    int pool_output_depth = pooling_layer->params.pool.shape.depth;
    int pool_output_size = pool_output_width * pool_output_height * pool_output_depth;
    DATA3D pool_output_data;
    initialize_DATA3D(&pool_output_data, pool_output_width, pool_output_height, pool_output_depth);

    if (pooling(pooling_layer, &conv_output_data, &pool_output_data)) {
        printf("Pooling successful!\n");
        printf("Pooling Output:\n");
        for (int i = 0; i < pool_output_size; ++i) {
            printf("%f ", pool_output_data.raw_data[i]);
        }
        printf("\n");
    } else {
        fprintf(stderr, "Pooling failed!\n");
        return EXIT_FAILURE;
    }

    free(matrix.raw_data);
    free(matrix.linearized_data.raw_data);
    free(kernel.raw_data);
    free(kernel.linearized_data.raw_data);
    free(conv_output_data.raw_data);
    free(pool_output_data.raw_data);

    return 0;
}
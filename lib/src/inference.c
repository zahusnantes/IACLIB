#include <stdio.h>
#include <stdlib.h>

#include "../inc/tools.h"
#include "../inc/images.h"
#include "../inc/conv.h"
#include "../inc/pooling.h"
#include "../inc/fc.h"
#include "../inc/inference.h"

void inference(CNN *cnn, DATA3D *input_matrix, DATA3D *kernel, DATA2D *weight_matrix, DATA1D *biases) {
    // Find the layers needed for inference
    Layer *conv_layer = find_layer(cnn, "conv1");
    Layer *pooling_layer = find_layer(cnn, "pool1");
    Layer *fc_layer = find_layer(cnn, "fc1");

    // Convolution
    DATA3D conv_output_data;
    int conv_output_size = conv_layer->data.shape.height * conv_layer->data.shape.width * conv_layer->data.shape.depth;
    initialize_DATA3D(&conv_output_data, conv_layer->data.shape.height, conv_layer->data.shape.width, conv_layer->data.shape.depth);
    if (conv(conv_layer, input_matrix, kernel, &conv_output_data)) {
        printf("Convolution Output:\n");
        for (int i = 0; i < conv_output_size; ++i) {
            printf("%f ", conv_output_data.raw_data[i]);
        }
        printf("\n");    } else {
        fprintf(stderr, "Convolution failed!\n");
    }

    // Pooling
    DATA3D pool_output_data;
    initialize_DATA3D(&pool_output_data, pooling_layer->data.shape.height, pooling_layer->data.shape.width, pooling_layer->data.shape.depth);
    if (pooling(pooling_layer, &conv_output_data, &pool_output_data)) {
        printf("Pooling Output:\n");
    } else {
        fprintf(stderr, "Pooling failed!\n");
    }

    // Fully Connected (FC) Layer
    int num_output_neurons = fc_layer->params.fc.shape.length;

    DATA3D fc_output_data;
    initialize_DATA3D(&fc_output_data, 1, 1, num_output_neurons);

    if (fc(fc_layer, &pool_output_data, weight_matrix, biases, &fc_output_data)) {
        printf("FC Output:\n");
    } else {
        fprintf(stderr, "FC Layer failed!\n");

    }

}
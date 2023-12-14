#include <stdio.h>
#include <stdlib.h>

#include "../inc/tools.h"
#include "../inc/data.h"
#include "../inc/conv.h"
#include "../inc/pooling.h"
#include "../inc/fc.h"
#include "../inc/inference.h"

int main() {
    DATA3D matrix;
    matrix.shape.width = 3;
    matrix.shape.height = 3;
    matrix.shape.depth = 1;
    initialize_DATA3D(&matrix, matrix.shape.height, matrix.shape.width, matrix.shape.depth);
    for (int i = 0; i < matrix.shape.width * matrix.shape.height * matrix.shape.depth; ++i) {
        matrix.raw_data[i] = i;
    }

    DATA3D kernel;
    kernel.shape.width = 2;
    kernel.shape.height = 2;
    kernel.shape.depth = 2;
    initialize_DATA3D(&kernel, kernel.shape.height, kernel.shape.width, kernel.shape.depth);
    for (int i = 0; i < kernel.shape.width * kernel.shape.height * kernel.shape.depth; ++i) {
        kernel.raw_data[i] = i;
    }

    DATA2D weight_matrix;
    int num_output_neurons = 2;
    initialize_DATA2D(&weight_matrix, 1 * 1 * 2, num_output_neurons);
    for (int i = 0; i < weight_matrix.shape.height; ++i) {
        for (int j = 0; j < weight_matrix.shape.width; ++j) {
            weight_matrix.raw_data[i * weight_matrix.shape.width + j] = i + j;
        }
    }

    DATA1D biases;
    initialize_DATA1D(&biases, num_output_neurons);

    int nb_classes = 2;

    CNN *cnn = read_model("../model/MNIST/model_cnn.dat", matrix.shape.height, matrix.shape.width, matrix.shape.depth, nb_classes);
    
    //bool success = read_weights(cnn, "../model/model_parameters.csv");

    inference(cnn, &matrix, &kernel, &weight_matrix, &biases);

    free(matrix.raw_data);
    free(kernel.raw_data);
    free(weight_matrix.raw_data);
    free(biases.raw_data);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>

#include "../inc/tools.h"
#include "../inc/data.h"
#include "read_mnist.hpp"
#include "../inc/inference.h"

char images_path[] = "../model/MNIST/t10k-images-idx3-ubyte.gz";
char labels_path[] = "../model/MNIST/t10k-labels-idx1-ubyte.gz";
char model_path[] = "../model/MNIST/model_cnn.dat";

int main() {

    DATA4D mnist_data = read_mnist_images(images_path);
    DATA1D mnist_labels_data = read_mnist_labels(labels_path);

    if (mnist_data.raw_data != nullptr && mnist_labels_data.raw_data != nullptr) {
        int num_rows = mnist_data.shape.height;
        int num_cols = mnist_data.shape.width;

        printf("num_rows = %d, num_cols = %d\n", num_rows, num_cols);

        for (int i = 0; i < num_rows; ++i) {
            for (int j = 0; j < num_cols; ++j) {
                std::cout << std::setw(5) << mnist_data.raw_data[0 * num_rows * num_cols + i * num_cols + j] << " ";
            }
            std::cout << " | Label: " << std::setw(5) << mnist_labels_data.raw_data[i] << std::endl;
        }
        free_data_4D(mnist_data);
        free_data_1D(mnist_labels_data);
    } else {
        std::cerr << "Failed to load image or label data." << std::endl;
    }

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

    CNN *cnn = read_model(model_path, matrix.shape.height, matrix.shape.width, matrix.shape.depth, nb_classes);
    
    //bool success = read_weights(cnn, "../model/model_parameters.csv");

    inference(cnn, &matrix, &kernel, &weight_matrix, &biases);

    free(matrix.raw_data);
    free(kernel.raw_data);
    free(weight_matrix.raw_data);
    free(biases.raw_data);

    return 0;
}
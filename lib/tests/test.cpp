#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>

#include "../inc/tools.h"
#include "../inc/data.h"
#include "mnist_dataset/read_mnist.hpp"
#include "../inc/inference.h"

char images_path[] = "../model/MNIST/t10k-images-idx3-ubyte.gz";
char labels_path[] = "../model/MNIST/t10k-labels-idx1-ubyte.gz";
char model_path[] = "../model/TEST/model_cnn.dat";
char model_parameters_path[] = "../model/TEST/model_parameters_test.csv";

int main() {

    DATA3D matrix;
    matrix.shape.width = 3;
    matrix.shape.height = 3;
    matrix.shape.depth = 1;
    initialize_DATA3D(&matrix, matrix.shape.height, matrix.shape.width, matrix.shape.depth);
    for (int i = 0; i < matrix.shape.width * matrix.shape.height * matrix.shape.depth; ++i) {
        matrix.raw_data[i] = i;
    }

    int nb_classes = 2;

    CNN *cnn = read_model(model_path, matrix.shape.height, matrix.shape.width, matrix.shape.depth, nb_classes);
    
    bool success = read_weights(cnn, model_parameters_path);

    inference(cnn, &matrix);

    free(matrix.raw_data);

    return 0;
}
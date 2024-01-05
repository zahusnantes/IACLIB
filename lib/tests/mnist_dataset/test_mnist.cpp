#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>

#include "../../inc/tools.h"
#include "../../inc/data.h"
#include "read_mnist.hpp"
#include "../../inc/inference.h"

char images_path[] = "../model/MNIST/t10k-images-idx3-ubyte.gz";
char labels_path[] = "../model/MNIST/t10k-labels-idx1-ubyte.gz";
char model_path[] = "../model/model.dat";
char model_parameters[] = "../model/model_parameters.csv";

int main() {

    DATA4D mnist_data = read_mnist_images(images_path);
    DATA1D mnist_labels_data = read_mnist_labels(labels_path);

    int input_height = 28;
    int input_width = 28;
    int input_depth = 1;
    int nb_classes = 10;

    CNN *cnn = read_model(model_path, input_height, input_width, input_depth, nb_classes);
    
    bool success = read_weights(cnn, model_parameters);

    DATA3D input;
    initialize_DATA3D(&input, input_height, input_width, input_depth);

    int correct_predictions = 0;
    int total_samples = mnist_labels_data.shape.length;

    for (int sample_index = 0; sample_index < total_samples; ++sample_index) {
        // Copy image data to input
        for (int d = 0; d < input_depth; ++d) {
            for (int h = 0; h < input_height; ++h) {
                for (int w = 0; w < input_width; ++w) {
                    input.raw_data[d * input_height * input_width + h * input_width + w] =
                        mnist_data.raw_data[sample_index * input_height * input_width * input_depth +
                                            d * input_height * input_width +
                                            h * input_width + w];
                }
            }
        }

        // Perform inference
        inference(cnn, &input);

        // Check prediction accuracy
        if (mnist_labels_data.raw_data[sample_index] == cnn->out_classes.raw_data[sample_index]) {
            correct_predictions++;
        }
    }

    double accuracy = static_cast<double>(correct_predictions) / total_samples * 100.0;
    std::cout << "Accuracy on the test set: " << std::fixed << std::setprecision(2) << accuracy << "%" << std::endl;

    return 0;
}

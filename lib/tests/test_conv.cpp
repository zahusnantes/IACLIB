#include <gtest/gtest.h>

#include "../inc/data.h"
#include "../inc/conv.h"
#include "../inc/tools.h"

constexpr int matrix_shape_width = 3;
constexpr int matrix_shape_height = 3;
constexpr int matrix_shape_depth = 1;
constexpr int kernel_shape_width = 2;
constexpr int kernel_shape_height = 2;
constexpr int kernel_shape_depth = 2;
constexpr int num_output_neurons = 2;
constexpr int nb_classes = 2;

TEST(ConvTest, BasicConvTest) {

    DATA3D matrix;
    matrix.shape.width = matrix_shape_width;
    matrix.shape.height = matrix_shape_height;
    matrix.shape.depth = matrix_shape_depth;
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
    kernel.shape.width = kernel_shape_width;
    kernel.shape.height = kernel_shape_height;
    kernel.shape.depth = kernel_shape_depth;
    initialize_DATA3D(&kernel, kernel.shape.height, kernel.shape.width, kernel.shape.depth);
    DATA1D linearized_kernel;
    initialize_DATA1D(&kernel.linearized_data, kernel.shape.width * kernel.shape.height * kernel.shape.depth);
    for (int i = 0; i < kernel.shape.width * kernel.shape.height * kernel.shape.depth; ++i) {
        kernel.raw_data[i] = i;
    }
    for (int i = 0; i < kernel.linearized_data.shape.length; ++i) {
        kernel.linearized_data.raw_data[i] = kernel.raw_data[i];
    }

    DATA2D weight_matrix;
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

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

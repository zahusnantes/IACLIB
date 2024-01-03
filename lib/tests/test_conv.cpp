#include <gtest/gtest.h>

#include <stdio.h>
#include <stdlib.h>

#include "../inc/tools.h"
#include "../inc/data.h"
#include "../inc/conv.h"
#include "test_tools.hpp"

TEST(ConvSizes, ConvSizesTest) {

    DATA3D input;
    create_matrix(&input, input_shape_height, input_shape_width, input_shape_depth);
    for (int i = 0; i < input.shape.width * input.shape.height * input.shape.depth; ++i) {
        input.raw_data[i] = i;
    }

    DATA3D kernel;
    create_matrix(&kernel, kernel_shape_height, kernel_shape_width, kernel_shape_depth);
    for (int i = 0; i < kernel.shape.width * kernel.shape.height * kernel.shape.depth; ++i) {
        kernel.raw_data[i] = i;
    }

    CNN *cnn = read_model(model_path, input.shape.height, input.shape.width, input.shape.depth, nb_classes);

    Layer *conv_layer = find_layer(cnn, conv1);

    CNNKernels *conv_params = &(conv_layer->params.kernels);

    int expected_output_height = (input.shape.width - kernel.shape.width + 2 * conv_layer->params.kernels.padding) / conv_layer->params.kernels.stride + 1;
    int expected_output_width = (input.shape.height - kernel.shape.height + 2 * conv_layer->params.kernels.padding) / conv_layer->params.kernels.stride + 1;
    int expected_num_channels = kernel.shape.depth;
    int expected_output_size = expected_output_height * expected_num_channels * expected_output_width;
    DATA3D expected_output;
    initialize_DATA3D(&expected_output, expected_output_height, expected_output_width, expected_num_channels);

    int conv_output_height = conv_params->shape.height;
    int conv_output_width = conv_params->shape.width;
    int conv_num_channels = conv_params->shape.depth;
    int conv_output_size = conv_layer->data.shape.height * conv_layer->data.shape.width * conv_layer->data.shape.depth;
    DATA3D conv_output;
    initialize_DATA3D(&conv_output, conv_output_height, conv_output_width, conv_num_channels);

    EXPECT_EQ(expected_output_height, conv_output_height);
    EXPECT_EQ(expected_output_width, conv_output_height);
    EXPECT_EQ(expected_num_channels, conv_num_channels);
    EXPECT_EQ(expected_output_size, conv_output_size);

    free(input.raw_data);
    free(kernel.raw_data);
    free(expected_output.raw_data);
    free(conv_output.raw_data);
}

TEST(ConvOutput, ConvOutputTest) {

    DATA3D input;
    create_matrix(&input, input_shape_height, input_shape_width, input_shape_depth);
    for (int i = 0; i < input.shape.width * input.shape.height * input.shape.depth; ++i) {
        input.raw_data[i] = i;
    }

    DATA3D kernel;
    create_matrix(&kernel, kernel_shape_height, kernel_shape_width, kernel_shape_depth);
    for (int i = 0; i < kernel.shape.width * kernel.shape.height * kernel.shape.depth; ++i) {
        kernel.raw_data[i] = i;
    }

    CNN *cnn = read_model(model_path, input.shape.height, input.shape.width, input.shape.depth, nb_classes);

    Layer *conv_layer = find_layer(cnn, conv1);

    CNNKernels *conv_params = &(conv_layer->params.kernels);

    double expected_output_values[] = {19.000000, 25.000000, 37.000000, 43.000000, 51.000000, 73.000000, 117.000000, 139.000000};
    int expected_output_height = (input.shape.width - kernel.shape.width + 2 * conv_layer->params.kernels.padding) / conv_layer->params.kernels.stride + 1;
    int expected_output_width = (input.shape.height - kernel.shape.height + 2 * conv_layer->params.kernels.padding) / conv_layer->params.kernels.stride + 1;
    int expected_num_channels = kernel.shape.depth;
    int expected_output_size = expected_output_height * expected_num_channels * expected_output_width;
    DATA3D expected_output;
    initialize_DATA3D(&expected_output, expected_output_height, expected_output_width, expected_num_channels);
    for (int c = 0; c < expected_num_channels; ++c) {
        for (int h = 0; h < expected_output_height; ++h) {
            for (int w = 0; w < expected_output_width; ++w) {
                int index = c * (expected_output_height * expected_output_width) + h * expected_output_width + w;
                expected_output.raw_data[index] = expected_output_values[index];
            }
        }
    }

    int conv_output_height = conv_params->shape.height;
    int conv_output_width = conv_params->shape.width;
    int conv_num_channels = conv_params->shape.depth;
    int conv_output_size = conv_layer->data.shape.height * conv_layer->data.shape.width * conv_layer->data.shape.depth;
    DATA3D conv_output;
    initialize_DATA3D(&conv_output, conv_output_height, conv_output_width, conv_num_channels);

    bool result = conv(conv_layer, &input, &kernel, &conv_output);

    ASSERT_TRUE(result);

    for (int i = 0; i < expected_output_size; ++i) {
        EXPECT_DOUBLE_EQ(conv_output.raw_data[i], expected_output.raw_data[i]);
    }

    free(input.raw_data);
    free(kernel.raw_data);
    free(expected_output.raw_data);
    free(conv_output.raw_data);
}

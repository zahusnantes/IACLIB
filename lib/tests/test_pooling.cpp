#include <gtest/gtest.h>

#include <stdio.h>
#include <stdlib.h>
#include <cmath>

#include "../inc/tools.h"
#include "../inc/data.h"
#include "../inc/conv.h"
#include "../inc/pooling.h"

TEST(PoolSizes, PoolSizesTest) {

    DATA3D input;
    input.shape.width = input_shape_width;
    input.shape.height = input_shape_height;
    input.shape.depth = input_shape_depth;
    initialize_DATA3D(&input, input.shape.height, input.shape.width, input.shape.depth);
    for (int i = 0; i < input.shape.width * input.shape.height * input.shape.depth; ++i) {
        input.raw_data[i] = i;
    }

    DATA3D kernel;
    kernel.shape.width = kernel_shape_width;
    kernel.shape.height = kernel_shape_height;
    kernel.shape.depth = kernel_shape_depth;
    initialize_DATA3D(&kernel, kernel.shape.height, kernel.shape.width, kernel.shape.depth);
    for (int i = 0; i < kernel.shape.width * kernel.shape.height * kernel.shape.depth; ++i) {
        kernel.raw_data[i] = i;
    }

    CNN *cnn = read_model(model_path, input.shape.height, input.shape.width, input.shape.depth, nb_classes);

    Layer *conv_layer = find_layer(cnn, conv1);
    Layer *pool_layer = find_layer(cnn, pool1);

    CNNKernels *conv_params = &(conv_layer->params.kernels);
    CNNPool *pooling_params = &(pool_layer->params.pool);

    int expected_conv_output_height = (input.shape.width - kernel.shape.width + 2 * conv_layer->params.kernels.padding) / conv_layer->params.kernels.stride + 1;
    int expected_conv_output_width = (input.shape.height - kernel.shape.height + 2 * conv_layer->params.kernels.padding) / conv_layer->params.kernels.stride + 1;
    int expected_conv_num_channels = kernel.shape.depth;

    int expected_pool_output_height = floor((expected_conv_output_height - pool_layer->params.pool.shape.height + 2 * pool_layer->params.pool.padding) / pool_layer->params.pool.stride) + 1;
    int expected_pool_output_width = floor((expected_conv_output_width - pool_layer->params.pool.shape.width + 2 * pool_layer->params.pool.padding) / pool_layer->params.pool.stride) + 1;
    int expected_pool_num_channels = expected_conv_num_channels;

    int expected_pool_output_size = expected_pool_output_height * expected_pool_num_channels * expected_pool_output_width;
    DATA3D expected_pool_output;
    initialize_DATA3D(&expected_pool_output, expected_pool_output_height, expected_pool_output_width, expected_pool_num_channels);

    int pool_output_height = pool_layer->data.shape.height;
    int pool_output_width = pool_layer->data.shape.width;
    int pool_num_channels = pool_layer->data.shape.depth;
    int pool_output_size = pool_output_height * pool_output_width * pool_num_channels;
    DATA3D pool_output;
    initialize_DATA3D(&pool_output, pool_output_height, pool_output_width, pool_num_channels);

    EXPECT_EQ(expected_pool_output_height, pool_output_height);
    EXPECT_EQ(expected_pool_output_width, pool_output_height);
    EXPECT_EQ(expected_pool_num_channels, pool_num_channels);
    EXPECT_EQ(expected_pool_output_size, pool_output_size);

    free(input.raw_data);
    free(kernel.raw_data);
    free(expected_pool_output.raw_data);
    free(pool_output.raw_data);
}

TEST(PoolOutput, PoolOutputTest) {

    DATA3D input;
    input.shape.width = input_shape_width;
    input.shape.height = input_shape_height;
    input.shape.depth = input_shape_depth;
    initialize_DATA3D(&input, input.shape.height, input.shape.width, input.shape.depth);
    for (int i = 0; i < input.shape.width * input.shape.height * input.shape.depth; ++i) {
        input.raw_data[i] = i;
    }

    DATA3D kernel;
    kernel.shape.width = kernel_shape_width;
    kernel.shape.height = kernel_shape_height;
    kernel.shape.depth = kernel_shape_depth;
    initialize_DATA3D(&kernel, kernel.shape.height, kernel.shape.width, kernel.shape.depth);
    for (int i = 0; i < kernel.shape.width * kernel.shape.height * kernel.shape.depth; ++i) {
        kernel.raw_data[i] = i;
    }

    CNN *cnn = read_model(model_path, input.shape.height, input.shape.width, input.shape.depth, nb_classes);

    Layer *conv_layer = find_layer(cnn, conv1);
    Layer *pool_layer = find_layer(cnn, pool1);

    CNNKernels *conv_params = &(conv_layer->params.kernels);
    CNNPool *pooling_params = &(pool_layer->params.pool);

    double expected_MAX_output_values[] = {117.00000, 139.00000};
    double expected_MIN_output_values[] = {19.00000, 51.00000};
    double expected_AVG_output_values[] = {56.00000, 70.00000};

    int expected_conv_output_height = (input.shape.width - kernel.shape.width + 2 * conv_layer->params.kernels.padding) / conv_layer->params.kernels.stride + 1;
    int expected_conv_output_width = (input.shape.height - kernel.shape.height + 2 * conv_layer->params.kernels.padding) / conv_layer->params.kernels.stride + 1;
    int expected_conv_num_channels = kernel.shape.depth;
    int expected_pool_output_height = floor((expected_conv_output_height - pool_layer->params.pool.shape.height + 2 * pool_layer->params.pool.padding) / pool_layer->params.pool.stride) + 1;
    int expected_pool_output_width = floor((expected_conv_output_width - pool_layer->params.pool.shape.width + 2 * pool_layer->params.pool.padding) / pool_layer->params.pool.stride) + 1;
    int expected_pool_num_channels = expected_conv_num_channels;
    int expected_pool_output_size = expected_pool_output_height * expected_pool_num_channels * expected_pool_output_width;
    DATA3D expected_pool_output;
    initialize_DATA3D(&expected_pool_output, expected_pool_output_height, expected_pool_output_width, expected_pool_num_channels);

    for (int c = 0; c < expected_pool_num_channels; ++c) {
        for (int h = 0; h < expected_pool_output_height; ++h) {
            for (int w = 0; w < expected_pool_output_width; ++w) {
                int index = c * (expected_pool_output_height * expected_pool_output_width) + h * expected_pool_output_width + w;
                switch (pool_layer->params.pool.type)
                {
                case MAX:
                    expected_pool_output.raw_data[index] = expected_MAX_output_values[index];
                    break;
                case MIN:
                    expected_pool_output.raw_data[index] = expected_MIN_output_values[index];
                    break;
                case AVG:
                    expected_pool_output.raw_data[index] = expected_AVG_output_values[index];
                    break;
                }
            }
        }
    }

    int pool_output_height = pool_layer->data.shape.height;
    int pool_output_width = pool_layer->data.shape.width;
    int pool_num_channels = pool_layer->data.shape.depth;
    int pool_output_size = pool_output_height * pool_output_width * pool_num_channels;
    DATA3D pool_output;
    initialize_DATA3D(&pool_output, pool_output_height, pool_output_width, pool_num_channels);

    int conv_output_height = conv_params->shape.height;
    int conv_output_width = conv_params->shape.width;
    int conv_num_channels = conv_params->shape.depth;
    int conv_output_size = conv_layer->data.shape.height * conv_layer->data.shape.width * conv_layer->data.shape.depth;
    DATA3D conv_output;
    initialize_DATA3D(&conv_output, conv_output_height, conv_output_width, conv_num_channels);

    bool conv_result = conv(conv_layer, &input, &kernel, &conv_output);
    bool result = pooling(pool_layer, &conv_output, &pool_output);

    ASSERT_TRUE(result);

    for (int i = 0; i < expected_pool_output_size; ++i) {
        EXPECT_DOUBLE_EQ(pool_output.raw_data[i], expected_pool_output.raw_data[i]);
    }

    free(input.raw_data);
    free(kernel.raw_data);
    free(expected_pool_output.raw_data);
    free(pool_output.raw_data);
}

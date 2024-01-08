#include <gtest/gtest.h>

#include <stdio.h>
#include <stdlib.h>

#include "../inc/tools.h"
#include "../inc/data.h"
#include "../inc/fc.h"
#include "test_tools.hpp"

TEST(FcSizes, FcSizesTest) {

    DATA3D input;
    initialize_DATA3D(&input, input_shape_height, input_shape_width, input_shape_depth);
    for (int i = 0; i < input_shape_width * input_shape_height * input_shape_depth; ++i) {
        input.raw_data[i] = i;
    }

    CNN *cnn = read_model(model_path, input.shape.height, input.shape.width, input.shape.depth, nb_classes);
    bool success = read_weights(cnn, model_parameters_path);

    Layer *conv_layer = find_layer(cnn, conv1);
    Layer *pool_layer = find_layer(cnn, pool1);
    Layer *fc_layer = find_layer(cnn, fc1);

    CNNKernels *conv_params = &(conv_layer->params.kernels);
    CNNPool *pooling_params = &(pool_layer->params.pool);
    CNNFc *fc_params = &(fc_layer->params.fc);

    int expected_fc_output_length = num_output_neurons;
    
    DATA1D expected_fc_output;
    initialize_DATA1D(&expected_fc_output, expected_fc_output_length);

    int fc_output_length = fc_params->shape.length;
    DATA1D fc_output;
    initialize_DATA1D(&fc_output, fc_output_length);

    EXPECT_EQ(expected_fc_output_length, fc_output_length);

    free(input.raw_data);
    free(expected_fc_output.raw_data);
    free(fc_output.raw_data);
}

TEST(FcOutput, FcOutputTest) {

    DATA3D input;
    initialize_DATA3D(&input, input_shape_height, input_shape_width, input_shape_depth);
    for (int i = 0; i < input_shape_width * input_shape_height * input_shape_depth; ++i) {
        input.raw_data[i] = i;
    }

    CNN *cnn = read_model(model_path, input.shape.height, input.shape.width, input.shape.depth, nb_classes);
    bool success = read_weights(cnn, model_parameters_path);

    Layer *conv_layer = find_layer(cnn, conv1);
    Layer *pool_layer = find_layer(cnn, pool1);
    Layer *fc_layer = find_layer(cnn, fc1);

    CNNKernels *conv_params = &(conv_layer->params.kernels);
    CNNPool *pooling_params = &(pool_layer->params.pool);
    CNNFc *fc_params = &(fc_layer->params.fc);

    int expected_fc_output_length = num_output_neurons;
    
    double expected_MAX_output_values[] = {139.00000, 321.00000};
    double expected_MIN_output_values[] = {51.00000, 121.00000};
    double expected_AVG_output_values[] = {95.00000, 221.00000};

    DATA1D expected_fc_output;
    initialize_DATA1D(&expected_fc_output, expected_fc_output_length);

    int fc_output_length = fc_params->shape.length;
    DATA3D fc_output;
    initialize_DATA3D(&fc_output, 1, 1, num_output_neurons);

    for (int c = 0; c < expected_fc_output_length; ++c) {
                switch (pool_layer->params.pool.type)
                {
                case MAX:
                    expected_fc_output.raw_data[c] = expected_MAX_output_values[c];
                    break;
                case MIN:
                    expected_fc_output.raw_data[c] = expected_MIN_output_values[c];
                    break;
                case AVG:
                    expected_fc_output.raw_data[c] = expected_AVG_output_values[c];
                    break;
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

    bool conv_result = conv(conv_layer, &input, &conv_output);
    bool pool_result = pooling(pool_layer, &conv_output, &pool_output);
    bool result = fc(fc_layer, &pool_output, &fc_output);

    ASSERT_TRUE(result);

    for (int i = 0; i < expected_fc_output_length; ++i) {
        EXPECT_DOUBLE_EQ(fc_output.raw_data[i], expected_fc_output.raw_data[i]);
    }

    free(input.raw_data);
    free(expected_fc_output.raw_data);
    free(fc_output.raw_data);
}


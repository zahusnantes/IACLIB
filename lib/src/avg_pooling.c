#include "../inc/pooling.h"
#include "../inc/tools.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void avg_pooling(Layer *pooling_layer, DATA3D *input_data, DATA3D *output_data) {

    CNNPool *pooling_params = &(pooling_layer->params.pool);

    int input_width = pooling_layer->bottom->data.shape.width;
    int input_height = pooling_layer->bottom->data.shape.height;
    int input_depth = pooling_layer->bottom->data.shape.depth;
    int input_size = input_height * input_width * input_depth;
    int pool_size = pooling_params->shape.width;
    int padding = pooling_params->padding;
    int stride = pooling_params->stride;
    int output_height = pooling_layer->data.shape.height;
    int output_width = pooling_layer->data.shape.width;
    int num_channels = pooling_layer->data.shape.depth;
    int output_size = output_height * output_width * num_channels;
    PoolingType pool_type = pooling_layer->params.pool.type;

    WEIGHT_TYPE result_value = 0.0;

    for (int c_output = 0; c_output < num_channels; ++c_output) {
        for (int h = 0; h < output_height; ++h) {
            for (int w = 0; w < output_width; ++w) {
                result_value = 0.0; 

                for (int i = 0; i < pool_size; ++i) {
                    for (int j = 0; j < pool_size; ++j) {
                        int input_idx = (h * stride + i) * input_width * num_channels + (w * stride + j) * num_channels + c_output;
                        if (input_idx >= 0 && input_idx < input_size) {
                            double input_pixel = input_data->raw_data[input_idx];
                            result_value += input_pixel;
                        }
                    }
                }
                if (pool_type == AVG) {
                    result_value /= (pool_size * pool_size);
                }
                // Store the result value in the output_data
                int output_idx = c_output * output_width * output_height + h * output_width + w;
                output_data->raw_data[output_idx] = result_value;
                }
            }
        }

}


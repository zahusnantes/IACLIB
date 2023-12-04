#include "../inc/pooling.h"
#include "../inc/tools.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

bool pooling(Layer *pooling_layer, DATA1D *input_data, DATA1D *output_data, int input_height, int input_width, int num_channels) {
    if (pooling_layer->type != MAX && pooling_layer->type != AVG && pooling_layer->type != MIN) {
        fprintf(stderr, "Error: Unsupported pooling type.\n");
        return false;  
    }

    CNNPool *pooling_params = &(pooling_layer->params.pool);

    int input_size = input_data->shape.length;
    int output_size = output_data->shape.length;
    int pool_size = pooling_params->shape.width;
    int padding = pooling_params->padding;
    int stride = pooling_params->stride;
    int output_height = input_height / pool_size;
    int output_width = input_width / pool_size;
    PoolingType pool_type = pooling_layer->params.pool.type;

    // Check if the output_data has the expected size
    if (output_size != num_channels * output_width * output_height) {
        fprintf(stderr, "Error: Output data size does not match expected size.\n");
        printf("output size = %d, num_channels = %d, output_width = %d, output_height = %d\n", output_size, num_channels, output_width, output_height);
        return false;  
    }
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
                            if (pool_type == MAX) {
                                // Max pooling
                                result_value = fmax(result_value, input_pixel);
                            } else if (pool_type == AVG) {
                                // Average pooling
                                result_value += input_pixel;
                            } else if (pool_type == MIN) {
                                // Min pooling
                                result_value = (i == 0 && j == 0) ? input_pixel : fmin(result_value, input_pixel);
                            }
                        }
                    }
                }

                // Finish average pooling calculation
                if (pool_type == AVG) {
                    result_value /= (pool_size * pool_size);
                }

                // Store the result value in the output_data
                int output_idx = c_output * output_width * output_height + h * output_width + w;
                output_data->raw_data[output_idx] = result_value;
                }
            }
        }

    return true; 
}


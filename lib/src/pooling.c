#include "../inc/pooling.h"
#include "../inc/tools.h"

#include <stdlib.h>
#include <stdio.h>

bool pooling(Layer *pooling_layer, DATA1D *input_data, DATA1D *output_data, int input_height, int input_width) {
    if (pooling_layer->type != MAX_POOLING) {
        fprintf(stderr, "Error: Layer is not a max pooling layer.\n");
        return false;  // Indicate failure
    }

    PoolingParams *pooling_params = &(pooling_layer->params.pooling);

    int input_size = input_data->shape.length;
    int output_size = output_data->shape.length;
    int num_channels = pooling_params->shape.depth;
    int pooling_size = pooling_params->shape.width;
    int padding = pooling_params->padding;
    int stride = pooling_params->stride;
    int output_height = (input_height - pooling_size + 2 * padding) / stride + 1;
    int output_width = (input_width - pooling_size + 2 * padding) / stride + 1;

    // Check if the output_data has the expected size
    if (output_size != num_channels * output_width * output_height) {
        fprintf(stderr, "Error: Output data size does not match expected size.\n");
        return false;  // Indicate failure
    }

    for (int c_output = 0; c_output < num_channels; ++c_output) {
        for (int h = 0; h < output_height; ++h) {
            for (int w = 0; w < output_width; ++w) {
                // Initialize max value for each output element
                WEIGHT_TYPE max_value = -INFINITY;

                for (int i = 0; i < pooling_size; ++i) {
                    for (int j = 0; j < pooling_size; ++j) {
                        int input_idx = (h * stride + i) * input_width * num_channels + (w * stride + j) * num_channels + c_output;
                        
                        // Check if the input index is within bounds
                        if (input_idx >= 0 && input_idx < input_size) {
                            double input_pixel = input_data->raw_data[input_idx];
                            max_value = fmax(max_value, input_pixel);
                        }
                    }
                }

                // Store the max value in the output_data
                int output_idx = c_output * output_width * output_height + h * output_width + w;
                output_data->raw_data[output_idx] = max_value;
            }
        }
    }

    return true;  // Indicate success
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/tools.h"
#include "../inc/data.h"
#include "../inc/conv.h"
#include "../inc/pooling.h"
#include "../inc/fc.h"
#include "../inc/inference.h"
#include "../inc/activation.h"

bool inference(CNN *cnn, DATA3D *image, DATA3D *kernel, DATA2D *weight_matrix, DATA1D *biases) {
    bool status = true;
    Layer *iterator = cnn->layers;
    DATA3D *input = image;
    DATA3D output[2];
    unsigned output_idx = 0;

    while (NULL != iterator && true == status) {
        switch (iterator->type)
        {
        case CONVOLUTION:
            int conv_output_size = iterator->data.shape.height * iterator->data.shape.width * iterator->data.shape.depth;
            initialize_DATA3D(&output[output_idx], iterator->data.shape.height, iterator->data.shape.width, iterator->data.shape.depth);
            if (conv(iterator, input, kernel, &output[output_idx])) {
                printf("-- Convolution Succesful --\n");
                // printf("Convolution Output:\n");
                // for (int i = 0; i < conv_output_size; ++i) {
                //     printf("%f ", output[output_idx].raw_data[i]);
                // }
                // printf("\n");   
                // } 
                // else {
                // fprintf(stderr, "Convolution failed!\n");
            }
            apply_activation(&output[output_idx], iterator->activation);
            input = &output[output_idx];
            output_idx = (output_idx + 1) % 2;
            break;

        case POOLING:
            int pool_output_size = iterator->data.shape.height * iterator->data.shape.width * iterator->data.shape.depth;
            initialize_DATA3D(&output[output_idx], iterator->data.shape.height, iterator->data.shape.width, iterator->data.shape.depth);
            if (pooling(iterator, input, &output[output_idx])) {
                printf("-- Pooling Succesful --\n");
            //     printf("Pooling Output:\n");
            //     for (int i = 0; i < pool_output_size; ++i) {
            //         printf("%f ", output[output_idx].raw_data[i]);
            //     }
            //     printf("\n");  
            // } else {
            //     fprintf(stderr, "Pooling failed!\n");
            }
            apply_activation(&output[output_idx], iterator->activation);
            input = &output[output_idx];
            output_idx = (output_idx + 1) % 2;
            break;

        case FC:
            int num_output_neurons = iterator->params.fc.shape.length;
            initialize_DATA3D(&output[output_idx], 1, 1, num_output_neurons);
            if (fc(iterator, input, weight_matrix, biases, &output[output_idx])) {
                printf("-- Fully Connected Succesful --\n");
            //     printf("FC Output:\n");
            //     for (int i = 0; i < iterator->params.fc.shape.length; ++i) {
            //         printf("%f ", output[output_idx].raw_data[i]);
            //     }
            //     printf("\n"); 
            // } else {
            //     fprintf(stderr, "FC Layer failed!\n");
            }
            apply_activation(&output[output_idx], iterator->activation);
            input = &output[output_idx];
            output_idx = (output_idx + 1) % 2;
            break;

        default:
            break;
        }

        iterator = iterator->top;
    }

    return status;
}
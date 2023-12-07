#include "../inc/pooling.h"
#include "../inc/tools.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

bool pooling(Layer *pooling_layer, DATA3D *input_data, DATA3D *output_data) {
    if (pooling_layer->type != MAX && pooling_layer->type != AVG && pooling_layer->type != MIN) {
        fprintf(stderr, "Error: Unsupported pooling type.\n");
        return false;  
    }
    CNNPool *pooling_params = &(pooling_layer->params.pool);
    PoolingType pool_type = pooling_layer->params.pool.type;
    WEIGHT_TYPE result_value = 0.0;
    switch (pool_type)
    {
    case MAX:
        max_pooling(pooling_layer, input_data, output_data);
        break;

        case AVG:
        avg_pooling(pooling_layer, input_data, output_data);
        break;

        case MIN:
        min_pooling(pooling_layer, input_data, output_data);
        break;

        default:
        break;
    }

    return true;
}


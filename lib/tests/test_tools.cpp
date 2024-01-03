#include <stdio.h>
#include <stdlib.h>

#include "../inc/data.h"
#include "../inc/tools.h"

void create_matrix(DATA3D *input_data, int height, int width, int depth) {
    input_data->shape.width = width;
    input_data->shape.height = height;
    input_data->shape.depth = depth;
    initialize_DATA3D(input_data, height, width, depth);
}



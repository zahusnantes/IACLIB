#include "tools.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

void fatal_error(int errorCode, const char *message)
{
    fprintf(stderr, "Fatal Error %d : %s\n", errorCode, message);
    exit(EXIT_FAILURE);
}

void print_warning(const char *message)
{
    printf("\x1b[35mWarning: %s\x1b[0m\n", message);
}

bool initialize_CNNKernels(CNNKernels *kernels, int width, int height, int depth, int stride, int padding)
{
    kernels->shape.width = width;
    kernels->shape.height = height;
    kernels->shape.depth = depth;
    kernels->stride = stride;
    kernels->padding = padding;
    return true;
}

bool initialize_CNNPool(CNNPool *pool, int width, int height, int stride, int padding, PoolingType poolingType)
{
    pool->shape.width = width;
    pool->shape.height = height;
    pool->stride = stride;
    pool->padding = padding;
    pool->type = poolingType;
    return true;
}

bool initialize_CNNFc(CNNFc *fc, int num_output)
{
    fc->shape.length = num_output;
    return true;
}

bool initialize_DATA3D(DATA3D *data, int width, int height, int depth)
{
    data->raw_data = (DATA_TYPE *)malloc(sizeof(DATA_TYPE) * height * width * depth);
    data->shape.width = width;
    data->shape.height = height;
    data->shape.depth = depth;
    
    if (data->raw_data == NULL)
    {
        return false;
    }
    
    return true;
}

bool initialize_DATA2D(DATA2D *data, int width, int height)
{
    data->raw_data = (DATA_TYPE *)malloc(sizeof(DATA_TYPE) * height * width);
    data->shape.width = width;
    data->shape.height = height;
    if (data == NULL)
    {
        return false;
    }
    return true;
}

bool initialize_DATA1D(DATA1D *data, int length)
{
    data->raw_data = (DATA_TYPE *)malloc(sizeof(DATA_TYPE) * length);
    data->shape.length = length;
    if (data == NULL)
    {
        return false;
    }
    return true;
}

int output_size(Layer *layer)
{

    // CHIARA : to do??
}

bool parse_CNN(char *filename, CNN *cnn)
{

    FILE *file = fopen(filename, "r");
    if (file == NULL)
        fatal_error(-11, "Failed to open the input file.");

    Layer *last_inserted_layer = NULL;
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        char *token = strtok(line, " \t\n");
        if (token == NULL)
            continue;

        if (strcmp(token, "layer") == 0)
        {
            // Found the start of a new layer
            Layer *newLayer = (Layer *)malloc(sizeof(Layer));
            memset(newLayer, 0, sizeof(Layer));
            newLayer->top = NULL;
            newLayer->bottom = NULL;

            int size = 0;
            int stride = 1;
            int padding = 1;
            int outchannels = 1;
            PoolingType poolType = -1;
            // Read and parse the layer definition
            while (fgets(line, sizeof(line), file) != NULL)
            {
                token = strtok(line, " \t\n");
                if (token == NULL)
                    continue;

                if (strcmp(token, "name:") == 0)
                {
                    char *ln = strtok(NULL, " \t\n");
                    strncpy(newLayer->name, ln + 1, strlen(ln) - 2);
                    newLayer->name[strlen(ln) - 2] = '\0';
                }
                else if (strcmp(token, "type:") == 0)
                {
                    char type[64];
                    strncpy(type, strtok(NULL, " \t\n"), sizeof(type));
                    newLayer->type = str_to_layerType(type);
                }
                else if (strcmp(token, "bottom:") == 0)
                {
                    // Houssam:  for instance I will write them back to back
                    char bottom[64];
                    strncpy(bottom, strtok(NULL, " \t\n"), sizeof(bottom));
                    // print_warning("This function is not implemented, and will be processed back to back ");
                }
                else if (strcmp(token, "top:") == 0)
                {
                    // Houssam:  for instance I will write them back to back
                    char top[64];
                    strncpy(top, strtok(NULL, " \t\n"), sizeof(top));
                    // print_warning("This function is not implemented, and will be processed back to back ");
                }
                else if (strcmp(token, "num_output:") == 0)
                {
                    outchannels = atoi(strtok(NULL, " \t\n"));
                }
                else if (strcmp(token, "kernel_size:") == 0)
                {
                    size = atoi(strtok(NULL, " \t\n"));
                }
                else if (strcmp(token, "stride:") == 0)
                {
                    stride = atoi(strtok(NULL, " \t\n"));
                }
                else if (strcmp(token, "pad:") == 0)
                {
                    padding = atoi(strtok(NULL, " \t\n"));
                }

                else if (strcmp(token, "pool:") == 0)
                {
                    char poolTypestr[64];
                    char poolTypeValue[64];

                    strncpy(poolTypeValue, strtok(NULL, " \t\n"), sizeof(poolTypeValue));
                    
                    poolType = str_to_poolingType(poolTypeValue);

                    if (poolType == -1)
                    {
                        print_warning("Unknown pooling type. Setting it to MAX by default.");
                        poolType = MAX; // Set to MAX pooling by default
                    }
                }

                else if (strcmp(token, "}") == 0)
                {
                    switch (newLayer->type)
                    {
                    case CONVOLUTION:

                        if (!initialize_CNNKernels(&newLayer->params.kernels, size, size, outchannels, stride, padding))
                        {
                            fatal_error(-44, "can't initialize CNNKernels");
                        }
                        break;

                    case POOLING:
                        if (!initialize_CNNPool(&newLayer->params.pool, size, size, stride, padding, poolType))
                        {
                            fatal_error(-55, "can't initialize CNNPool");
                        }
                        break;

                    case FC:
                        if (!initialize_CNNFc(&newLayer->params.fc, outchannels))
                        {
                            fatal_error(-55, "can't initialize CNNFc");
                        }
                        break;

                    default:
                        break;
                    }

                    if (cnn->layers == NULL)
                    {
                        cnn->layers = newLayer;
                    }
                    else
                    {
                        last_inserted_layer->top = newLayer;
                    }
                    last_inserted_layer = newLayer;
                    break;
                }
            }
        }
    }
    fclose(file);
}

bool compute_layer_conv_params(Layer *iterator, Shape3D shape)
{

    iterator->data.shape.depth = shape.depth;

    iterator->data.shape.width = ((shape.width + 2 * iterator->params.kernels.padding - iterator->params.kernels.shape.width) / iterator->params.kernels.stride) + 1;
    iterator->data.shape.height = ((shape.height + 2 * iterator->params.kernels.padding - iterator->params.kernels.shape.height) / iterator->params.kernels.stride) + 1;

    int weight_size = (iterator->bottom == NULL) ? CNN_kernels_params_count(iterator->params.kernels, 1) : CNN_kernels_params_count(iterator->params.kernels, iterator->bottom->data.shape.depth);
    printf("Layer %s -> %d \n", iterator->name, weight_size);

    iterator->params.kernels.values_size = weight_size;
    if ((iterator->params.kernels.values = (WEIGHT_TYPE *)malloc(sizeof(WEIGHT_TYPE) * weight_size)) == NULL)
    {
        return false;
    }
    if ((iterator->params.kernels.bias = (WEIGHT_TYPE *)malloc(sizeof(WEIGHT_TYPE) * iterator->params.kernels.shape.depth)) == NULL)
    {
        return false;
    }

    return true;
}

bool compute_layer_pool_params(Layer *iterator)
{

    Shape3D shape = iterator->bottom->data.shape;
    iterator->data.shape.depth = iterator->bottom->params.kernels.shape.depth;
    iterator->data.shape.width = floor((shape.width - iterator->params.pool.shape.width) / iterator->params.pool.stride) + 1;
    iterator->data.shape.height = floor((shape.width - iterator->params.pool.shape.width) / iterator->params.pool.stride) + 1;
    return true;
}

bool compute_layer_fc_params(Layer *iterator)
{
    int weight_size = iterator->params.fc.shape.length * layer_data_size(iterator->bottom);
    iterator->params.fc.values_size = weight_size;
    printf("weight_size -> %d \n", weight_size);
    iterator->params.fc.values = (WEIGHT_TYPE *)malloc(sizeof(WEIGHT_TYPE) * weight_size);
    iterator->params.fc.bias = (WEIGHT_TYPE *)malloc(sizeof(WEIGHT_TYPE) * iterator->params.fc.shape.length);
    
    iterator->data.shape.width = iterator->params.fc.shape.length;
    iterator->data.shape.height = 1;
    iterator->data.shape.depth = 1;
    return iterator->params.fc.values != NULL && iterator->params.fc.bias != NULL;
}

bool calculate_check_params(CNN *cnn)
{
    // linking bottom and top (not very important regarding the current implemetation)
    Layer *iterator = cnn->layers->top;
    Layer *bottom = cnn->layers;
    iterator->bottom = NULL;
    while (iterator != NULL)
    {
        iterator->bottom = bottom;
        bottom = bottom->top;
        iterator = iterator->top;
    }
    // Calcululating the different sizes

    iterator = cnn->layers;

    // We must calculate the depth and the shape of the output
    Shape3D shape = {cnn->in_data.shape.width, cnn->in_data.shape.height, 1};
    compute_layer_conv_params(iterator, shape);
    iterator = iterator->top;
    while (iterator != NULL)
    {
        switch (iterator->type)
        {
        case CONVOLUTION:
            compute_layer_conv_params(iterator, iterator->bottom->data.shape);
            break;

        case POOLING:
            compute_layer_pool_params(iterator);
            break;

        case FC:
            compute_layer_fc_params(iterator);
            break;

        default:
            break;
        }

        iterator = iterator->top;
    }
}
CNN *read_model(char *filename, int in_h, int in_w, int nb_classes)
{
    CNN *cnn = (CNN *)malloc(sizeof(CNN));
    if (cnn == NULL)
        return NULL;
    cnn->layers = NULL;
    // initialize the input data
    initialize_DATA2D(&cnn->in_data, in_w, in_h);
    // intialize the output classes vector
    initialize_DATA1D(&cnn->out_classes, nb_classes);

    // parsing the file
    parse_CNN(filename, cnn);
    // calculating the CNN parameters
    calculate_check_params(cnn);

    return cnn;
}
LayerType str_to_layerType(char *str)
{
    if (strcmp(str, "\"Convolution\"") == 0)
        return CONVOLUTION;
    if (strcmp(str, "\"Pooling\"") == 0)
        return POOLING;
    if (strcmp(str, "\"InnerProduct\"") == 0)
        return FC;
    printf("%s \n", str);
    fatal_error(-11, "Uknown Layer type");
    return UNKOWN;
}
char *layerType_to_str(LayerType type)
{
    if (type == CONVOLUTION)
        return "Convolution";

    if (type == POOLING)
        return "Pooling";
    if (type == FC)
        return "InnerProduct";
    if (type == UNKOWN)
        return "Unknown";
}

char *poolingType_to_str(PoolingType type)
{
    switch (type)
    {
    case MAX:
        return "MAX";
        break;
    case AVG:
        return "AVG";
        break;
    case SOFTMAX:
        return "SOFTMAX";
        break;

    default:
        break;
    }
    return "UNKNOWN";
}

PoolingType str_to_poolingType(char *str)
{
    if (strcmp(str, "MAX") == 0)
        return MAX;
    if (strcmp(str, "AVG") == 1) //CHIARA: before everything was 0, i change it, is it correct?
        return AVG;
    if (strcmp(str, "SOFTMAX") == 2) //CHIARA: before everything was 0, i change it, is it correct?
        return SOFTMAX;
    printf("%s \n", str);
    fatal_error(-11, "Uknown Poolin type");
    return -1;
}

void display_kernels_minimal(CNNKernels *kernels)
{
    printf("[Kernel: width: %d, height: %d, depth: %d, stride: %d, padding: %d]\n",
           kernels->shape.width, kernels->shape.height, kernels->shape.depth, kernels->stride, kernels->padding);
}

void display_kernels_complete(CNNKernels *kernels)
{
    print_warning("this function shoud  display all the weights of the kernels");
}

void display_pool(CNNPool *pool)
{
    printf("[Pool: width %d, height %d,  stride %d, padding: %d, type : %s]\n",
           pool->shape.width, pool->shape.height, pool->stride, pool->padding, poolingType_to_str(pool->type));
}

void display_FC(CNNFc *fc)
{
    printf("[FC: Neuron Count  %d ]\n", fc->shape.length);
}

void display_Shape3D(Shape3D *shape)
{
    printf("[Shape3D: width %d, height %d, depth %d ]", shape->width, shape->height, shape->depth);
}

void display_layer(Layer *layer)
{

    printf("[Layer: \n");
    printf("\t Name: %s\n", layer->name);
    printf("\t Type: %s\n", layerType_to_str(layer->type));
    if (layer->bottom != NULL)
        printf("\t bottom: %s\n", layer->bottom->name);

    printf("\t DATA shape:");
    display_Shape3D(&layer->data.shape);
    printf("\n \t ");
    switch (layer->type)
    {
    case CONVOLUTION:
        display_kernels_minimal(&layer->params.kernels);
        break;

    case POOLING:
        display_pool(&layer->params.pool);
        break;

    case FC:
        display_FC(&layer->params.fc);
        break;

    default:
        break;
    }
    if (layer->top != NULL)
        printf("\t top: %s\n", layer->top->name);

    printf("]\n");
}
void display_cnn(CNN *cnn)
{
    Layer *iterator = cnn->layers;
    while (iterator != NULL)
    {
        display_layer(iterator);
        iterator = iterator->top;
    }
}
Layer *find_layer(CNN *cnn, char *layer_name)
{
    Layer *iterator = cnn->layers;
    while (iterator != NULL)
    {
        if (strcmp(layer_name, iterator->name) == 0)
            return iterator;
        iterator = iterator->top;
    }
    return NULL;
}
void parse_first_column(char *token, char *p1, char *p2)
{
    char *dot_position = strchr(token, '.'); // Find the position of the dot
    if (dot_position != NULL)
    {
        size_t length_p1 = dot_position - token;
        size_t length_p2 = strlen(token) - length_p1 - 1;
        strncpy(p1, token, length_p1);
        p1[length_p1] = '\0';
        strncpy(p2, dot_position + 1, length_p2);
        p2[length_p2] = '\0';
    }
    else
    {
        fatal_error(-55, "Invalid first column");
    }
}

bool fill_array(int size, char *token, WEIGHT_TYPE *array)
{
    printf("fill array called with size %d \n", size);
    int count = 0;
    while ((token = strtok(NULL, ",")) != NULL)
    {
        WEIGHT_TYPE value;
        if (sscanf(token, WEIGHT_PARSE_SIGNATURE, &value) == 1)
        {
            if (count < size)
            {
                array[count] = value;
            
            }
            else
            {
                return false;
            }
        }
        count++;
    }

    return count==size;
}

int CNN_kernels_params_count(CNNKernels kernels, int previous_channel_count)
{
    printf("Calculating kernel parameters:\n");
    printf("  Previous Channel Count: %d\n", previous_channel_count);
    printf("  Depth: %d\n", kernels.shape.depth);
    printf("  Height: %d\n", kernels.shape.height);
    printf("  Width: %d\n", kernels.shape.width);
    
    return previous_channel_count * kernels.shape.depth * kernels.shape.height * kernels.shape.width;
}

int layer_data_size(Layer *layer)
{

    if (layer->type == CONVOLUTION || layer->type == POOLING)
        return layer->data.shape.depth * layer->data.shape.height * layer->data.shape.width;
    else
        return layer->params.fc.shape.length;
}

bool read_weights(CNN *cnn, char *filename)
{
    FILE *file = fopen(filename, "r"); // Replace "your_file.csv" with your file path
    if (file == NULL)
        fatal_error(-112, "Failed to open the file.\n");

    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, file) != -1)
    {
        char *token;
        token = strtok(line, ",");
        // Parse the first column
        char name[50], weight_type[50];
        parse_first_column(token, name, weight_type);

        Layer *current_layer = find_layer(cnn, name);
        if (current_layer == NULL)

            {
                printf("Layer name : %s \n", name);
                fatal_error(-113, "Failed to find the layer");
            }

        // check the type to know what to fill
        if (current_layer->type == CONVOLUTION)
        {
            if (strcmp(weight_type, "weight") == 0)
            {
                if (!fill_array(current_layer->params.kernels.values_size, token, current_layer->params.kernels.values))
                {
                    fatal_error(-112, "Failed to fill weight for the current convolution layer");
                }
            }
            if (strcmp(weight_type, "bias") == 0)
            {
                if (!fill_array(current_layer->params.kernels.shape.depth, token, current_layer->params.kernels.bias))
                {
                    fatal_error(-112, "Failed to fill weight for the current convolution layer");
                }
            }
        }
        else if (current_layer->type == FC)
        {
            if (strcmp(weight_type, "weight") == 0)
            {
                if (!fill_array(current_layer->params.fc.values_size, token, current_layer->params.fc.values))
                {
                    fatal_error(-112, "Failed to fill weight for the current convolution layer");
                }
            }

                  if (strcmp(weight_type, "bias") == 0)
            {
                if (!fill_array(current_layer->params.fc.shape.length, token, current_layer->params.fc.bias))
                {
                    fatal_error(-112, "Failed to fill weight for the current convolution layer");
                }
            }
        }
        else
        {
            fatal_error(-1, "Unkown paramter to parse");
        }
    }
    free(line);
    fclose(file);

    return true;
}

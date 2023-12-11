#ifndef TOOLS_H
#define TOOLS_H

#include <stdbool.h>
#include <images.h>

// CNN Parameters
#define WEIGHT_TYPE double
#define DATA_TYPE double
#define WEIGHT_PARSE_SIGNATURE "%lf"

// GPU parameters
#define GPU_GRANULARITY 10

// CPU parallel parameters
#define CPU_GRANULARITY 50

typedef enum
{
    CONVOLUTION,
    POOLING,
    FC,
    UNKOWN
} LayerType;


typedef enum
{
    RELU,
    SIGMOID,
    SOFTMAX
} Activation;

typedef enum
{
    MAX,
    AVG,
    MIN
} PoolingType;

typedef struct
{
    Shape3D shape;
    int padding, stride;
    int values_size;
    WEIGHT_TYPE *values;
    WEIGHT_TYPE *bias;
} CNNKernels;

typedef struct
{
    Shape1D shape;
    int values_size;
    WEIGHT_TYPE *values;
    WEIGHT_TYPE * bias;
} CNNFc;

typedef struct
{
    Shape3D shape;
    int padding, stride;
    PoolingType type;
} CNNPool;

union LayerPars
{
    CNNKernels kernels; // Kernel
    CNNPool pool;       // Pool
    CNNFc fc;           // Pool
};

typedef union LayerPars LayerParams;

struct Layer
{
    char name[32];
    Activation activation;
    DATA3D data;
    struct Layer *top;
    struct Layer *bottom;
    LayerType type;
    LayerParams params;
};

typedef struct Layer Layer;

typedef struct
{
    DATA3D in_data;
    DATA1D out_classes;
    Layer *layers;
} CNN;

void fatal_error(int errorCode, const char *message);
void print_warning(const char *message);

// Houssam: peut etre homogénéiser celle là pour prendre les des parametres similaire
bool initialize_CNNKernels(CNNKernels *kernels, int width, int height, int depth, int stride, int padding);
bool initialize_CNNPool(CNNPool *pool, int width, int height, int stride, int padding, PoolingType poolingType);
bool initialize_CNNFc(CNNFc *fc, int num_output);

int output_size(Layer *layer);

bool initialize_DATA1D(DATA1D *data, int length);
bool initialize_DATA2D(DATA2D *data, int width, int height);
bool initialize_DATA3D(DATA3D *data, int width, int height, int depth);
//bool initialize_layer(Layer *layer);

int CNN_kernels_params_count(CNNKernels kernels, int previous_channel_count);

CNN *read_model(char *filename, int in_h, int in_w, int int_d, int nb_classes);

Layer *find_layer(CNN *cnn, char *layer_name);
void parse_first_column(char *token, char *p1, char *p2);
bool fill_array(int size, char *token, WEIGHT_TYPE *array);
bool read_weights(CNN *cnn, char *filename);
bool parse_CNN(char *filename, CNN *cnn);
bool calculate_check_params(CNN *cnn);

int layer_data_size(Layer *layer);

void display_Shape3D(Shape3D *shape);
void display_FC(CNNFc *fc);
char *layerType_to_str(LayerType type);
LayerType str_to_layerType(char *str);


char *poolingType_to_str(PoolingType type);
PoolingType str_to_poolingType(char *str);

void display_layer(Layer *layer);
void display_cnn(CNN *cnn);

#endif
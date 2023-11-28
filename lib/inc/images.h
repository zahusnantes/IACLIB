#ifndef DATA_H
#define DATA_H

#include <stdbool.h>

// CNN Parameters
#define WEIGHT_TYPE double
#define DATA_TYPE double
#define WEIGHT_PARSE_SIGNATURE "%lf"

typedef struct
{
    int length;
} Shape1D;

typedef struct
{
    int width, height;
} Shape2D;

typedef struct
{
    int width, height, depth;
} Shape3D;

typedef struct
{
    int width, height, depth, num_images;
} Shape4D; // CHIARA: created in order to read the data set of images

typedef struct
{
    Shape2D shape;
    DATA_TYPE *raw_data;
} DATA2D;

typedef struct
{
    Shape1D shape;
    DATA_TYPE *raw_data;
} DATA1D;

typedef struct
{
    Shape3D shape;
    DATA_TYPE *raw_data;
    DATA1D linearized_data;  // CHIARA: New field for linearized data
} DATA3D;

typedef struct
{
    Shape4D shape;
    DATA_TYPE *raw_data;
} DATA4D;

#endif
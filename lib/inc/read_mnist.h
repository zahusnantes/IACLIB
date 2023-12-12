#include <stdio.h>
#include <stdlib.h>
#include <../inc/data.h>
#include "../inc/tools.h"

typedef struct {
    int magic_number;
    int num_images;
    int num_rows;
    int num_cols;
} ImageHeader;

typedef struct {
    unsigned char **pixels;
} Image;

Image read_mnist_images(const char *filename);
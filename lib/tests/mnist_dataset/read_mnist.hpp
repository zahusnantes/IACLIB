#include <iostream>
#include <fstream>

#include "../inc/tools.h"
#include "../inc/data.h"

DATA4D read_mnist_images(const std::string &filename);
void free_data_4D(DATA4D &data);
DATA1D read_mnist_labels(const std::string &filename);
void free_data_1D(DATA1D &data);
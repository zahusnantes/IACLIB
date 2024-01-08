#ifndef TEST_TOOLS_H
#define TEST_TOOLS_H

#include <iostream>
#include <fstream>

constexpr int input_shape_width = 3;
constexpr int input_shape_height = 3;
constexpr int input_shape_depth = 1;
constexpr int kernel_shape_width = 2;
constexpr int kernel_shape_height = 2;
constexpr int kernel_shape_depth = 2;
constexpr int num_output_neurons = 2;
constexpr int nb_classes = 2;
char model_path[] = "../model/TEST/model_cnn.dat";
char model_parameters_path[] = "../model/TEST/model_parameters_test.csv";
char conv1[] = "conv1";
char pool1[] = "pool1";
char fc1[] = "fc1";

void create_matrix(DATA3D *input_data, int height, int width, int depth);

#endif
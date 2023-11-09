#include "tools.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    CNN *cnn = read_model("../model/model.dat", 28, 28, 10);
   // display_cnn(cnn);
   bool success = read_weights(cnn, "../model/model_parameters.csv");

    // preprocess input 
    // faire l'inference

    if (success)
        printf("Model parameters loaded successfully");
    else
        fatal_error(-111, "Model parameters loading failed");


}
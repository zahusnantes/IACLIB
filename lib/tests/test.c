#include <stdio.h>
#include <stdlib.h>
#include "../inc/tools.h"

int main() {
    char modelFilename[] = "../model/model.dat";

    int in_h = 28;
    int in_w = 28;
    int nb_classes = 10;

    CNN *cnn = read_model(modelFilename, in_h, in_w, nb_classes);
    if (cnn == NULL) {
        fprintf(stderr, "Failed to read the model.\n");
        return EXIT_FAILURE;
    }

    display_cnn(cnn);

    free(cnn->in_data.raw_data);
    free(cnn->out_classes.raw_data);
    free(cnn);

    return EXIT_SUCCESS;
}

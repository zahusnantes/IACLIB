#include "../inc/node.hpp"
#include "data.h"
#include "tools.h"

#include <iostream>

int main(int argc, char **argv){

    DATA3D matrix;
    matrix.shape.width = 3;
    matrix.shape.height = 3;
    matrix.shape.depth = 1;
    initialize_DATA3D(&matrix, matrix.shape.height, matrix.shape.width, matrix.shape.depth);
    for (int i = 0; i < matrix.shape.width * matrix.shape.height * matrix.shape.depth; ++i) {
        matrix.raw_data[i] = i;
    }

    int height = 5;
    int width = 5;

    Node node;
    int memorySize = node.totalMemorySize(&height, &width);
    std::cout << "Memory Size: " << memorySize << std::endl;

    return 0;
}


// int i_shape2D_x = 640;
// int i_shape2D_y = 480;

// int f_shape2D_x = 5;
// int f_shape2D_y = 5;


// int m = 6;

// std::vector<Node> node_list;
// for (int i=0;i< SHAPE_OUTPUT;i++)
// {
//     Node  n();
//     n.operations.insert({MULTIPLCATION, 25});
//     n.operations.insert({ADDITION, 24});
    
//     Calculer l'index de index_debut et index_fin 
//     pour chaque copy memoire à faire 

// }


// // L'objectif est de réduire le temps d'exécution
// // de notre Convolution-> Réduire lastest C time 
// }
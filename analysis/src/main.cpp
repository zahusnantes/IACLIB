#include "../inc/node.hpp"
#include "data.h"
#include "tools.h"

#include <iostream>

int main(int argc, char **argv){

    DATA3D input;
    input.shape.width = 3;
    input.shape.height = 3;
    input.shape.depth = 1;
    initialize_DATA3D(&input, input.shape.height, input.shape.width, input.shape.depth);
    for (int i = 0; i < input.shape.width * input.shape.height * input.shape.depth; ++i) {
        input.raw_data[i] = i;
    }

    DATA3D kernel;
    kernel.shape.width = 2;
    kernel.shape.height = 2;
    kernel.shape.depth = 1;
    initialize_DATA3D(&kernel, kernel.shape.height, kernel.shape.width, kernel.shape.depth);
    for (int i = 0; i < kernel.shape.width * kernel.shape.height * kernel.shape.depth; ++i) {
        kernel.raw_data[i] = i;
    }

    int padding = 0;
    int stride = 1;

    DATA3D output;
    output.shape.depth = kernel.shape.depth;
    output.shape.width = ((input.shape.width + 2 * padding - kernel.shape.width) / stride) + 1;
    output.shape.height = ((input.shape.height + 2 * padding - kernel.shape.height) / stride) + 1;
    initialize_DATA3D(&output, output.shape.height, output.shape.width, output.shape.depth);
    int output_size = output.shape.height * output.shape.width * output.shape.depth;

    Node AtomicOperation;
    int memorySize = AtomicOperation.totalMemorySize(&kernel.shape.height, &kernel.shape.width);
    int totalcomputationTime = AtomicOperation.computationTime(&kernel.shape.height, &kernel.shape.width);
    int totalbatches = AtomicOperation.totalMemCopy(&kernel.shape.height);
    int totalmem = AtomicOperation.getMemCopyCount();
    // std::cout << "Memory Size: " << memorySize << std::endl;
    // std::cout << "Computation Time: " << totalcomputationTime << std::endl;
    // std::cout << "Total Batches: " << totalbatches << std::endl;
    std::cout << "Total Batches: " << totalmem << std::endl;

    std::vector<Node> node_list;
    for (int i = 0; i < output_size; ++i) {
        std::string node_name = "Node" + std::to_string(i);
        Node node(node_name);
        node_list.push_back(node);
    }

    for (size_t i = 0; i < node_list.size(); ++i) {
        std::cout << "Node " << i + 1 << ":\n";
        std::cout << "Node " << node_list[i].getMemCopyCount() << ":\n";
        for (size_t j = 0; j < node_list[i].getMemCopyCount(); ++j) {
            int startIndex = node_list[i].getStartIndexForMemCopy(j);
            int finishIndex = node_list[i].getFinishIndexForMemCopy(j);
            std::cout << "  MemCopy " << j + 1 << ": Start Index = " << startIndex << ", Finish Index = " << finishIndex << "\n";
        }
    }

    return 0;
}

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
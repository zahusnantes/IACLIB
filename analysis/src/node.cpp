#include "../inc/node.hpp"
#include "data.h"

#include <iostream>

MemCopy::MemCopy() : start_index(0), finish_index(0) {}

MemCopy::~MemCopy() {}

Node::Node() {}

Node::~Node() {}

int Node::totalMemorySize(int* kernel_height, int* kernel_width) const {
    int totalSize = 0;
    if (kernel_height && kernel_width) {
        totalSize = (*kernel_height) * (*kernel_width) * 2;
    }
    return totalSize;
}

int Node::computationTime(int* kernel_height, int* kernel_width){
    int totalTime = 0;
    if (kernel_height && kernel_width) {
        totalTime = (*kernel_height) * (*kernel_width) + ((*kernel_height) * (*kernel_width) - 1);

        operations[MULTIPLICATION] = *kernel_height * *kernel_width;
        operations[ADDITIONAL] = *kernel_height * *kernel_width - 1;
    }
    return totalTime;
}

int Node::totalMemCopy(int* kernel_height) {
    int batches = 0;
    if (kernel_height) {
        batches = (*kernel_height);
        MemCopy mem_copy;
        mem_copy.setStartIndex(0);
        mem_copy.setFinishIndex(*kernel_height);
        mem_copies.push_back(mem_copy);
    }
    return batches;
}

size_t Node::getMemCopyCount() const {
    return mem_copies.size();
}

// int Node::batchesMemCopy(int* batches, DATA3D *input_data, DATA3D *kernel) {

// }

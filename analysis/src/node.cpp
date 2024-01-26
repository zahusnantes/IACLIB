#include "../inc/node.hpp"
#include "data.h"

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

int Node::computationTime() {
    int totalTime = 0;
    // Calculate computation time based on your logic
    return totalTime;
}

int Node::memCpyDuration() {
    int totalDuration = 0;
    // Calculate memory copy duration based on your logic
    return totalDuration;
}

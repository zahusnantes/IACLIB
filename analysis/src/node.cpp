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

int Node::computationTime(int* kernel_height, int* kernel_width) const {
    int totalTime = 0;
    if (kernel_height && kernel_width) {
        totalTime = (*kernel_height) * (*kernel_width) + ((*kernel_height) * (*kernel_width) - 1);
    }
    return totalTime;
}

int Node::totalmemCopy(int* kernel_height) const {
    int totalDuration = 0;
    if (kernel_height) {
        totalDuration = (*kernel_height);
    }
    return totalDuration;
}

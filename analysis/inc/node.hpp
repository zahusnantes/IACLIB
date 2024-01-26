#ifndef NODE_HPP
#define NODE_HPP

#include <map>
#include <vector>

enum Operation
{
    MULTIPLICATION = 0,
    ADDITIONAL = 1,
    CONDITIONS = 2,
};

class MemCopy
{
private:
    int start_index, finish_index;

public:
    MemCopy();
    ~MemCopy();
};

class Node
{
private:
    std::map<enum Operation, int> operations;
    std::vector<MemCopy> mem_copies;
    std::vector<Node> children;

public:
    Node();
    ~Node();

    int totalMemorySize(int* kernel_height, int* kernel_width) const;
    int computationTime(int* kernel_height, int* kernel_width) const;
    int totalmemCopy(int* kernel_height) const;
};

#endif
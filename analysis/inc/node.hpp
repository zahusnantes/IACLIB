#ifndef NODE_HPP
#define NODE_HPP

#include <map>
#include <vector>
#include <iostream>

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

    void setStartIndex(int index) {
        start_index = index;
    }

    void setFinishIndex(int index) {
        finish_index = index;
    }

    int getStartIndex() const {
        return start_index;
    }

    int getFinishIndex() const {
        return finish_index;
    }
};



class Node
{
private:
    std::map<enum Operation, int> operations;
    std::vector<MemCopy> mem_copies;
    std::vector<Node> children;
    std::string name;

public:
    Node(); 

    Node(const std::string& node_name) : name(node_name) {};

    ~Node();

    void setName(const std::string& node_name) {
        name = node_name;
    }

    std::string getName() const {
        return name;
    }

    int totalMemorySize(int* kernel_height, int* kernel_width) const;
    int computationTime(int* kernel_height, int* kernel_width);
    int totalMemCopy(int* kernel_height);
    size_t getMemCopyCount() const;
    // int batchesMemCopy(int* batches, DATA3D *input_data, DATA3D *kernel);

    int getStartIndexForMemCopy(size_t index) const {
        if (index < mem_copies.size()) {
            return mem_copies[index].getStartIndex();
        } else {
            // Handle index out of bounds
            return -1; // Or throw an exception, return a default value, etc.
        }
    }

    int getFinishIndexForMemCopy(size_t index) const {
        if (index < mem_copies.size()) {
            return mem_copies[index].getFinishIndex();
        } else {
            // Handle index out of bounds
            return -1; // Or throw an exception, return a default value, etc.
        }
    }

};

#endif

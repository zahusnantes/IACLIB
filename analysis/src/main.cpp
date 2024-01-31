#include <iostream>
#include <fstream>
#include <yaml-cpp/yaml.h>

#include "../inc/node.hpp"
#include "../inc/platform.hpp"
#include "data.h"
#include "tools.h"

int main()
{
    PlatformParameters params;
    if (!parsePlatformParameters("../data/param.yaml", params))
    {
        std::cerr << "Error parsing YAML file " << std::endl;
    }

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

    std::vector<Node> node_list;
    for (int i = 0; i < output_size; ++i) {
        Node newNode(i + 1);
        newNode.setOperationCount(MULTIPLICATION, kernel.shape.width * kernel.shape.height);
        newNode.setOperationCount(ADDITION, kernel.shape.width * kernel.shape.height -1);
        for (int j = 0; j < kernel.shape.height; ++j) {
            MemCopy memCopy(i + 1, 0, 2, MM_TO_SM);
            newNode.addMemCpy(memCopy);
        }
        node_list.push_back(newNode);
    }
    for (const auto& node : node_list) {
        node.display();
    }


    // Node n1(1);
    // n1.setOperationCount(MULTIPLICATION, 9);
    // n1.setOperationCount(ADDITION, 8);
    // MemCopy c1(0, 2, MM_TO_SM);
    // MemCopy c2(9, 11, MM_TO_SM);
    // MemCopy c3(18, 20, MM_TO_SM);
    // n1.addMemCpy(c1);
    // n1.addMemCpy(c2);
    // n1.addMemCpy(c3);
    // n1.display();

    // Node n2(2);
    // n2.setOperationCount(MULTIPLICATION, 9);
    // n2.setOperationCount(ADDITION, 8);
    // MemCopy c4(1, 3, MM_TO_SM);
    // MemCopy c5(10, 12, MM_TO_SM);
    // MemCopy c6(19, 21, MM_TO_SM);
    // n2.addMemCpy(c4);
    // n2.addMemCpy(c5);
    // n2.addMemCpy(c6);
    // n2.display();

    // Node n3(3);
    // n3.setOperationCount(MULTIPLICATION, 9);
    // n3.setOperationCount(ADDITION, 8);
    // MemCopy c7(2, 8, MM_TO_SM);
    // MemCopy c8(11, 13, MM_TO_SM);
    // MemCopy c9(20, 22, MM_TO_SM);
    // n3.addMemCpy(c7);
    // n3.addMemCpy(c8);
    // n3.addMemCpy(c9);
    // n3.display();

    // Node n4(4);

    // n4.addChild(n1);
    // n4.addChild(n2);
    // n4.addChild(n3);

    // n4.mergeChildren();


    // std::vector<Node> atomic_node_list;
    // int H = 27;
    // int W = 27;

    // int k_h = 3;
    // int k_w = 3;

    // for (int i = 0; i < H; i++)
    // {
    //     for (int j = 0; j < W; j++)
    //     {

    //         Node n(i);
    //         Node n1(1);
    //         n.setOperationCount(MULTIPLICATION, k_h * k_w);
    //         n.setOperationCount(ADDITION, k_h * k_w - 1);
    //         for (int is = 0; is < k_h)
    //         {
    //             MemCopy c(i, i + k_w, MM_TO_SM);
    //             n.addMemCpy(c);
    //         }
    //     }
    // }

    //    n4.memCpyDuration(params);
    return 0;
}

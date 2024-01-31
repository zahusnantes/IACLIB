#include <iostream>
#include <fstream>
#include <yaml-cpp/yaml.h>
#include "../inc/node.hpp"
#include "data.h"
#include "tools.h"

struct PlatformParameters
{
    int core_count;
    int mem_per_core;
    int copy_cost;
    int copy_size;
    int cost_mem_op;
    int cost_mul_op;
    int cost_add_op;
};

bool parsePlatformParameters(const std::string &filename, PlatformParameters &params)
{
    try
    {
        YAML::Node config = YAML::LoadFile(filename);

        params.core_count = config["platform"]["core_count"].as<int>();
        params.mem_per_core = config["platform"]["mem_per_core"].as<int>();
        params.copy_cost = config["platform"]["copy_cost"].as<int>();
        params.copy_size = config["platform"]["copy_size"].as<int>();
        params.cost_mem_op = config["platform"]["cost_mem_op"].as<int>();
        params.cost_mul_op = config["platform"]["cost_mul_op"].as<int>();
        params.cost_add_op = config["platform"]["cost_add_op"].as<int>();

        return true;
    }
    catch (const YAML::Exception &e)
    {
        std::cerr << "Error parsing YAML file: " << e.what() << std::endl;
        return false;
    }
}

int main()
{
    PlatformParameters params;
    if (!parsePlatformParameters("../data/param.yaml", params))
    {
        std::cerr << "Error parsing YAML file " << std::endl;
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

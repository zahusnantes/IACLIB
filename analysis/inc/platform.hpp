#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include <iostream>
#include <fstream>

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

bool parsePlatformParameters(const std::string &filename, PlatformParameters &params);

#endif
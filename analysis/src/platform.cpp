#include <iostream>
#include <fstream>
#include <yaml-cpp/yaml.h>

#include "../inc/node.hpp"
#include "../inc/platform.hpp"
#include "data.h"
#include "tools.h"

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
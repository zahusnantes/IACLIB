#ifndef PLATFORM_HPP
#define PLATFORM_HPP

class PlatformParameters
{
    private:
    int core_count;
    int mem_per_core;
    int copy_cost;
    int copy_size;
    int cost_mem_op;
    int cost_mul_op;
    int cost_add_op;

    public:
    PlatformParameters();
    ~PlatformParameters();
};

#endif
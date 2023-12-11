#ifndef SOLUTION_H
#define SOLUTION_H

#include "common.h"

template <int DAY>
struct solution {
    virtual void part1(const std::string& input_path)
    {
        std::cout << "D" << DAY << " P1 not implemented";
    }

    virtual void part2(const std::string& input_path)
    {
        std::cout << "D" << DAY << " P2 not implemented";
    }

    virtual ~solution() { }
};

#endif // SOLUTION_H
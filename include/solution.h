#ifndef SOLUTION_H
#define SOLUTION_H

#include "common.h"

template <int DAY>
struct solution {
    virtual void part1(const std::string& input_path)
    {
        std::cout << "Day " << DAY << " part 1 not implemented yet.\n";
    }

    virtual void part2(const std::string& input_path)
    {
        std::cout << "Day " << DAY << " part 2 not implemented yet.\n";
    }

    virtual ~solution() { }
};

#endif // SOLUTION_H
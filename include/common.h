#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

/*
generic input reading function
returns a vector of strings that can be parsed later
*/
std::vector<std::string> get_input(const std::string& file_path)
{
    std::fstream input_file(file_path, std::ios::in);
    if ( !input_file.is_open() ) {
        throw std::runtime_error("COULD NOT OPEN FILE " + file_path);
    }

    std::vector<std::string> input;
    std::string line;
    while ( std::getline(input_file, line) ) {
        input.emplace_back(line);
    }

    return input;
}

template <typename T>
inline void print_solution(T solution, T expected_solution)
{
    if ( solution != expected_solution ) {
        std::cout << "Solution doesn't match expected value anymore: " << solution << " != " << expected_solution << "\n";
    }
    else {
        std::cout << solution;
    }
}

#endif // COMMON_H
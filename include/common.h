#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <cctype>

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

template <typename T>
inline std::vector<T> nr_string_to_vector(const std::string& input)
{
    std::istringstream ss(input);
    return std::vector<T>(std::istream_iterator<T>(ss), std::istream_iterator<T>());
}

#endif // COMMON_H
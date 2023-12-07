#include "../include/solution.h"

std::string& replace_literal_numbers(std::string& line)
{
    const std::vector <std::string> numbers = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

    for ( int i = 0; i < numbers.size(); ++i ) {
        size_t idx = 0;
        while ( (idx = line.find(numbers[i], idx)) != std::string::npos ) {
            line.replace(++idx, 1, std::to_string(i + 1));
        }
    }

    return line;
}

int parse_line(const std::string& line)
{
    int i, val = 0;

    for ( i = 0; i < line.size() && !(line[i] >= '0' && line[i] <= '9'); ++i ) { }
    val += 10 * (line[i] - '0');

    for ( i = line.size() - 1; i >= 0 && !(line[i] >= '0' && line[i] <= '9'); --i ) { }
    val += (line[i] - '0');

    return val;
}

template <>
void solution<1>::part1(const std::string& input_path)
{
    int res = 0;
    for ( auto& line : get_input(input_path) ) {
        res += parse_line(line);
    }

    const int expected_solution = 54697;
    print_solution(res, expected_solution);
}

template <>
void solution<1>::part2(const std::string& input_path)
{
    int res = 0;
    for ( auto& line : get_input(input_path) ) {
        res += parse_line(replace_literal_numbers(line));
    }

    const int expected_solution = 54885;
    print_solution(res, expected_solution);
}
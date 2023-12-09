#include "../include/solution.h"

static const std::array<std::string, 9> numbers = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

inline std::string& replace_literal_numbers(std::string& line)
{
    for ( int i = 0; i < numbers.size(); ++i ) {
        size_t idx = 0;
        while ( (idx = line.find(numbers[i], idx)) != std::string::npos ) {
            // "one" -> "o1e" (this way "twone" -> "t2o1e", instead of "2ne")
            line.replace(++idx, 1, std::to_string(i + 1));
        }
    }

    return line;
}

inline int parse_line_part1(const std::string& line)
{
    auto first_it = std::find_if(line.begin(), line.end(), [ ] (char c) { return std::isdigit(c); });
    auto last_it = std::find_if(line.rbegin(), line.rend(), [ ] (char c) { return std::isdigit(c); });

    int first_digit = first_it != line.end() ? *first_it - '0' : 0;
    int last_digit = last_it != line.rend() ? *last_it - '0' : 0;

    return 10 * first_digit + last_digit;
}

template <>
void solution<1>::part1(const std::string& input_path)
{
    std::vector<std::string> input = get_input(input_path);
    int res = std::accumulate(input.begin(), input.end(), 0, [ ] (int acc, std::string& line) {
        return acc + parse_line_part1(line);
    });

    const int expected_solution = 54697;
    print_solution(res, expected_solution);
}

template <>
void solution<1>::part2(const std::string& input_path)
{
    std::vector<std::string> input = get_input(input_path);
    int res = std::accumulate(input.begin(), input.end(), 0, [ ] (int acc, std::string& line) {
        return acc + parse_line_part1(replace_literal_numbers(line));
    });

    const int expected_solution = 54885;
    print_solution(res, expected_solution);
}
#include <chrono>
#include <iostream>

#include "solution.h"

#define IMPLEMENTATION_PATH_RELATIVE_TO_PROJECT_DIR "src/"
#define GET_PATH(DAY) IMPLEMENTATION_PATH_RELATIVE_TO_PROJECT_DIR "solution" + std::to_string(DAY) + ".cpp"

void print_time(const std::chrono::system_clock::time_point& start, const std::chrono::system_clock::time_point& end)
{
    std::chrono::duration<double> elapsed_seconds = end - start;
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_seconds);
    std::cout << " (" << ms.count() << " ms)\n";
}

template <int DAY, bool CHRONO, bool PRINT_IMPLEMENTED_ONLY>
void execute_day(const std::string& input_path)
{
    if constexpr ( PRINT_IMPLEMENTED_ONLY ) {
        std::string full_path = GET_PATH(DAY);
        std::ifstream ifs(full_path);
        if ( !ifs.good() ) {
            return;
        }
    }

    std::cout << "Day " << DAY << ":\n";
    const std::string part_1 = "Part 1: ";
    const std::string part_2 = "Part 2: ";

    solution<DAY> day;
    if constexpr ( CHRONO ) {
        std::cout << part_1;
        auto start = std::chrono::system_clock::now();
        day.part1(input_path);
        auto end = std::chrono::system_clock::now();
        print_time(start, end);

        std::cout << part_2;
        start = std::chrono::system_clock::now();
        day.part2(input_path);
        end = std::chrono::system_clock::now();
        print_time(start, end);
    }
    else {
        std::cout << part_1;
        day.part1(input_path);
        std::cout << "\n";

        std::cout << part_2;
        day.part2(input_path);
        std::cout << "\n";
    }

    std::cout << "\n";
}
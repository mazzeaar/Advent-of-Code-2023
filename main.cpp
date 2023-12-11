#include "include/solution.h"
#include "include/execute_day.h"

#include "src/solution1.cpp"
#include "src/solution2.cpp"
#include "src/solution3.cpp"
#include "src/solution4.cpp"
#include "src/solution5.cpp"
#include "src/solution6.cpp"
#include "src/solution7.cpp"
#include "src/solution8.cpp"
#include "src/solution9.cpp"
#include "src/solution10.cpp"
#include "src/solution11.cpp"

#define TIME_SOLUTIONS 1

#ifndef PRINT_ALL
#define PRINT_ALL 0
#endif

#ifndef PRINT_SPECIFIC_DAY
#define PRINT_SPECIFIC_DAY 0
#endif

#ifndef PRINT_SOLVED
#define PRINT_SOLVED 0
#endif

#if PRINT_ALL && PRINT_SPECIFIC_DAY
#   warning "PRINT_ALL and PRINT_SPECIFIC_DAY are both defined. PRINT_ALL will be ignored."
#   undef PRINT_ALL
#   define PRINT_ALL 0
#elif PRINT_SPECIFIC_DAY && PRINT_SOLVED
#   warning "PRINT_SPECIFIC_DAY and PRINT_SOLVED are both defined. PRINT_SOLVED will be ignored."
#   undef PRINT_SOLVED
#   define PRINT_SOLVED 0
#endif

int main()
{
    auto now = std::chrono::system_clock::now();
    std::time_t t_now = std::chrono::system_clock::to_time_t(now);
    std::tm* date = std::localtime(&t_now);

    int day = date->tm_mday;
    int month = date->tm_mon + 1;

    if ( PRINT_ALL || month != 12 || day > 25 ) {
        execute_day<1, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day1.txt");
        execute_day<2, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day2.txt");
        execute_day<3, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day3.txt");
        execute_day<4, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day4.txt");
        execute_day<5, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day5.txt");
        execute_day<6, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day6.txt");
        execute_day<7, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day7.txt");
        execute_day<8, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day8.txt");
        execute_day<9, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day9.txt");
        execute_day<10, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day10.txt");
        execute_day<11, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day11.txt");
        execute_day<12, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day12.txt");
        execute_day<13, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day13.txt");
        execute_day<14, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day14.txt");
        execute_day<15, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day15.txt");
        execute_day<16, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day16.txt");
        execute_day<17, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day17.txt");
        execute_day<18, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day18.txt");
        execute_day<19, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day19.txt");
        execute_day<20, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day20.txt");
        execute_day<21, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day21.txt");
        execute_day<22, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day22.txt");
        execute_day<23, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day23.txt");
        execute_day<24, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day24.txt");
        execute_day<25, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day25.txt");
    }
    else {
        if constexpr ( PRINT_SPECIFIC_DAY ) {
            execute_day<PRINT_SPECIFIC_DAY, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day" + std::to_string(PRINT_SPECIFIC_DAY) + ".txt");
        }
        else {
            switch ( day ) {
            case 1: execute_day<1, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day1.txt"); break;
            case 2: execute_day<2, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day2.txt"); break;
            case 3: execute_day<3, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day3.txt"); break;
            case 4: execute_day<4, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day4.txt"); break;
            case 5: execute_day<5, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day5.txt"); break;
            case 6: execute_day<6, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day6.txt"); break;
            case 7: execute_day<7, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day7.txt"); break;
            case 8: execute_day<8, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day8.txt"); break;
            case 9: execute_day<9, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day9.txt"); break;
            case 10: execute_day<10, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day10.txt"); break;
            case 11: execute_day<11, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day11.txt"); break;
            case 12: execute_day<12, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day12.txt"); break;
            case 13: execute_day<13, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day13.txt"); break;
            case 14: execute_day<14, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day14.txt"); break;
            case 15: execute_day<15, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day15.txt"); break;
            case 16: execute_day<16, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day16.txt"); break;
            case 17: execute_day<17, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day17.txt"); break;
            case 18: execute_day<18, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day18.txt"); break;
            case 19: execute_day<19, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day19.txt"); break;
            case 20: execute_day<20, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day20.txt"); break;
            case 21: execute_day<21, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day21.txt"); break;
            case 22: execute_day<22, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day22.txt"); break;
            case 23: execute_day<23, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day23.txt"); break;
            case 24: execute_day<24, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day24.txt"); break;
            case 25: execute_day<25, TIME_SOLUTIONS, PRINT_SOLVED>("input/input_day25.txt"); break;
            }
        }
    }
}
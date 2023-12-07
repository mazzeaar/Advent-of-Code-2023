#include "../include/solution.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <set>

inline bool is_symbol(char s)
{
    return s != '.' && !isdigit(s);
}

// inefficient but idc
bool is_part(const std::vector<std::vector<char>>& s, int row, int col, int nsize)
{
    for ( int i = 0; i < nsize; ++i ) {
        int currentCol = col + i;

        for ( int dr = -1; dr <= 1; ++dr ) {
            for ( int dc = -1; dc <= 1; ++dc ) {
                if ( dr == 0 && dc == 0 ) continue;

                int checkRow = row + dr;
                int checkCol = currentCol + dc;

                if ( checkRow >= 0 && checkRow < s.size() &&
                    checkCol >= 0 && checkCol < s[0].size() &&
                    is_symbol(s[checkRow][checkCol]) ) {
                    return true;
                }
            }
        }
    }

    return false;
}

std::vector<std::vector<char>> getinput(const std::string& path)
{
    std::vector<std::vector<char>> s;
    std::vector<std::string> input = get_input(path);

    for ( auto& line : input ) {
        std::vector<char> cline(line.begin(), line.end());
        s.push_back(cline);
    }

    return s;
}

unsigned long long gear_ratio(const std::vector<std::vector<char>>& s, int r, int c)
{
    std::set<int> unique_parts;

    for ( int dr = -1; dr <= 1; ++dr ) {
        for ( int dc = -1; dc <= 1; ++dc ) {
            if ( dr == 0 && dc == 0 ) continue;

            int checkRow = r + dr, checkCol = c + dc;
            if ( checkRow < 0 || checkRow >= s.size() || checkCol < 0 || checkCol >= s[0].size() ) continue;

            if ( isdigit(s[checkRow][checkCol]) && is_part(s, checkRow, checkCol, 1) ) {
                int startCol = checkCol;
                while ( startCol > 0 && isdigit(s[checkRow][startCol - 1]) ) startCol--;

                int number = 0;
                for ( int i = startCol; i < s[0].size() && isdigit(s[checkRow][i]); ++i ) {
                    number = number * 10 + (s[checkRow][i] - '0');
                }

                unique_parts.insert(number);
            }
        }
    }

    return unique_parts.size() == 2 ? *unique_parts.begin() * *(++unique_parts.begin()) : 0;
}

template <>
void solution<3>::part1(const std::string& input_path)
{
    std::vector<std::vector<char>> input = getinput(input_path);

    unsigned long long sum = 0;
    const int h = input.size();
    const int w = input[0].size();

    for ( int r = 0; r < h; ++r ) {
        for ( int c = 0; c < w; ++c ) {
            if ( isdigit(input[r][c]) ) {
                int nsize = 0;
                for ( int i = c; i < w && isdigit(input[r][i]); ++i ) {
                    nsize++;
                }

                if ( is_part(input, r, c, nsize) ) {
                    int number = 0;
                    for ( int i = c; i < c + nsize; ++i ) {
                        number = number * 10 + (input[r][i] - '0');
                    }
                    sum += number;
                }

                c += nsize - 1;
            }
        }
    }

    const unsigned long long expected_solution = 532331;
    print_solution(sum, expected_solution);
}

template <>
void solution<3>::part2(const std::string& input_path)
{
    std::vector<std::vector<char>> input = getinput(input_path);
    unsigned long long total_gear_ratio = 0;
    const int h = input.size();
    const int w = input[0].size();

    for ( int r = 0; r < h; ++r ) {
        for ( int c = 0; c < w; ++c ) {
            if ( input[r][c] == '*' ) {
                unsigned long long ratio = gear_ratio(input, r, c);
                total_gear_ratio += ratio;
            }
        }
    }

    const unsigned long long expected_solution = 82301120;
    print_solution(total_gear_ratio, expected_solution);
}
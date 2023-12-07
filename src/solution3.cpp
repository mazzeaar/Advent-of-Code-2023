#include "../include/solution.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <set>

inline bool is_symbol(char s)
{
    return s != '.' && !std::isdigit(s);
}

// inefficient but idc
bool is_part(const std::vector<std::string>& s, int row, int col, int nsize)
{
    for ( int i = 0; i < nsize; ++i ) {
        int currentCol = col + i;

        for ( int rowOffset = -1; rowOffset <= 1; ++rowOffset ) {
            for ( int colOffset = -1; colOffset <= 1; ++colOffset ) {
                if ( rowOffset == 0 && colOffset == 0 ) continue;

                int checkRow = row + rowOffset;
                int checkCol = currentCol + colOffset;

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

unsigned long long gear_ratio(const std::vector<std::string>& grid, int r, int c)
{
    std::set<int> unique_parts;

    for ( int rowOffset = -1; rowOffset <= 1; ++rowOffset ) {
        for ( int colOffset = -1; colOffset <= 1; ++colOffset ) {
            if ( rowOffset == 0 && colOffset == 0 ) continue;

            int checkRow = r + rowOffset, checkCol = c + colOffset;
            if ( checkRow < 0 || checkRow >= grid.size() || checkCol < 0 || checkCol >= grid[0].size() ) continue;

            if ( std::isdigit(grid[checkRow][checkCol]) && is_part(grid, checkRow, checkCol, 1) ) {
                int startCol = checkCol;
                while ( startCol > 0 && std::isdigit(grid[checkRow][startCol - 1]) ) startCol--;

                int number = 0;
                for ( int i = startCol; i < grid[0].size() && std::isdigit(grid[checkRow][i]); ++i ) {
                    number = number * 10 + (grid[checkRow][i] - '0');
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
    auto input = get_input(input_path);

    unsigned long long result = 0;
    const int h = input.size();
    const int w = input[0].size();

    for ( int r = 0; r < h; ++r ) {
        for ( int c = 0; c < w; ++c ) {
            if ( std::isdigit(input[r][c]) ) {
                int nsize = 0;
                for ( int i = c; i < w && std::isdigit(input[r][i]); ++i ) {
                    nsize++;
                }

                if ( is_part(input, r, c, nsize) ) {
                    int number = 0;
                    for ( int i = c; i < c + nsize; ++i ) {
                        number = number * 10 + (input[r][i] - '0');
                    }
                    result += number;
                }

                c += nsize - 1;
            }
        }
    }

    const unsigned long long expected_solution = 532331;
    print_solution(result, expected_solution);
}

template <>
void solution<3>::part2(const std::string& input_path)
{
    const std::vector<std::string> input = get_input(input_path);
    unsigned long long result = 0;

    for ( const auto& row : input ) {
        for ( const auto& col : row ) {
            if ( col == '*' ) {
                result += gear_ratio(input, &row - &input[0], &col - &row[0]);
            }
        }
    }

    const unsigned long long expected_solution = 82301120;
    print_solution(result, expected_solution);
}
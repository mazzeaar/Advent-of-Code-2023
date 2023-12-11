#include "../include/solution.h"

using grid = std::vector<std::string>;
using point = std::pair<int, int>;

const char EMPTY_SPACE = '.';
const char GALAXY = '#';

std::vector<point> get_galaxy_coordinates(grid& grid, int expansion_dist)
{
    std::vector<point> galaxies;
    for ( int row = 0; row < grid.size(); ++row ) {
        for ( int col = 0; col < grid[row].size(); ++col ) {
            if ( grid[row][col] == GALAXY ) {
                galaxies.push_back({ row, col });
            }
        }
    }

    std::vector<int> row_insert_positions;
    for ( int row = 0; row < grid.size(); ++row ) {
        if ( std::all_of(grid[row].begin(), grid[row].end(), [ ] (char c) { return c == EMPTY_SPACE; }) ) {
            row_insert_positions.push_back(row);
        }
    }

    std::vector<int> col_insert_positions;
    for ( int col = 0; col < grid[0].size(); ++col ) {
        bool empty = true;
        for ( int row = 0; row < grid.size(); ++row ) {
            empty &= grid[row][col] == EMPTY_SPACE;
        }

        if ( empty ) {
            col_insert_positions.push_back(col);
        }
    }

    for ( point& galaxy : galaxies ) {
        int add_to_row = 0;
        for ( int row_insert_pos : row_insert_positions ) {
            if ( galaxy.first > row_insert_pos ) {
                ++add_to_row;
            }
        }

        int add_to_col = 0;
        for ( int col_insert_pos : col_insert_positions ) {
            if ( galaxy.second > col_insert_pos ) {
                ++add_to_col;
            }
        }

        galaxy.first += (add_to_row * expansion_dist);
        galaxy.second += (add_to_col * expansion_dist);
    }

    return galaxies;
}


long long sum_manhattan(const std::vector<point>& galaxies)
{
    long long result = 0;
    for ( int i = 0; i < galaxies.size(); ++i ) {
        for ( int j = i + 1; j < galaxies.size(); ++j ) {
            result += std::abs(galaxies[i].first - galaxies[j].first) + std::abs(galaxies[i].second - galaxies[j].second);
        }
    }

    return result;
}

template <>
void solution<11>::part1(const std::string& input_path)
{
    grid grid = get_input(input_path);
    std::vector<point> galaxies = get_galaxy_coordinates(grid, 1);

    int result = sum_manhattan(galaxies);
    const int expected = 9648398;
    print_solution(result, expected);
}

template <>
void solution<11>::part2(const std::string& input_path)
{
    grid grid = get_input(input_path);
    std::vector<point> galaxies = get_galaxy_coordinates(grid, 999999);

    long long result = sum_manhattan(galaxies);

    const long long expected = 618800410814;
    print_solution(result, expected);
}
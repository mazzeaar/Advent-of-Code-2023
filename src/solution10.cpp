#include "../include/solution.h"

using memo = std::vector<std::vector<int>>;
using grid = std::vector<std::string>;
using point = std::pair<int, int>;

std::vector<std::pair<int, int>> neighbors(grid& grid, int i, int j)
{
    switch ( grid[i][j] ) {
    case '|': return { {i - 1, j}, {i + 1, j} };
    case '-': return { {i, j - 1}, {i, j + 1} };
    case 'L': return { {i - 1, j}, {i, j + 1} };
    case 'J': return { {i - 1, j}, {i, j- 1} };
    case '7': return { {i + 1, j}, {i, j - 1} };
    case 'F': return { {i + 1, j}, {i, j + 1} };
    default: throw std::runtime_error("well...\n");
    }
}

void print_memo(memo& memo)
{
    for ( auto& row : memo ) {
        for ( auto& col : row ) {
            if ( col != 2147483647 ) {
                std::cout << "#";
            }
            else {
                std::cout << ".";
            }
        }
        std::cout << "\n";
    }
}

inline bool isValid(grid& grid, int i, int j) { return i >= 0 && i < grid.size() && j >= 0 && j < grid[0].size() && grid[i][j] != '.'; }

point find_starting_point(grid& grid)
{
    for ( int i = 0; i < grid.size(); ++i ) {
        for ( int j = 0; j < grid[0].size(); ++j ) {
            if ( grid[i][j] == 'S' ) {
                return { i, j };
            }
        }
    }

    return { -1, -1 };
}

template <>
void solution<10>::part1(const std::string& input_path)
{
    grid grid = get_input(input_path);
    memo memo(grid.size(), std::vector<int>(grid[0].size(), std::numeric_limits<int>::max()));
    int result = 0;

    point start = find_starting_point(grid);
    grid[start.first][start.second] = 'F'; // solved the replacement letter visually
    memo[start.first][start.second] = 0;

    std::queue<point> queue;
    queue.emplace(start.first, start.second);

    // bfs
    while ( !queue.empty() ) {
        int row = queue.front().first;
        int col = queue.front().second;
        queue.pop();

        result = std::max(result, memo[row][col]);
        for ( point& point: neighbors(grid, row, col) ) {
            if ( isValid(grid, point.first, point.second) && memo[point.first][point.second] > memo[row][col] + 1 ) {
                memo[point.first][point.second] = memo[row][col] + 1;
                queue.emplace(point);
            }
        }
    }

    print_memo(memo);
    const int expected = 6968;
    print_solution(result, expected);
}

template <>
void solution<10>::part2(const std::string& input_path)
{
    grid grid = get_input(input_path);
}
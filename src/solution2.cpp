#include "../include/solution.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

struct cubes {
    int r, g, b;

    cubes() = default;
    cubes(int r, int g, int b) : r(r), g(g), b(b) { }
    cubes(const std::string& segment) : r(0), g(0), b(0)
    {
        std::istringstream segmentStream(segment);
        int quantity;
        std::string color;

        while ( segmentStream >> quantity >> color ) {
            if ( color.back() == ',' )
                color.pop_back();

            if ( color == "red" )
                r += quantity;
            else if ( color == "green" )
                g += quantity;
            else if ( color == "blue" )
                b += quantity;
        }
    }
};


static const std::map<std::string, int cubes::*> colorMap = { {"red", &cubes::r}, {"green", &cubes::g}, {"blue", &cubes::b} };

std::vector<cubes> parseGame(const std::string& line)
{
    std::vector<cubes> game;
    std::istringstream ss(line);
    std::string segment;

    while ( std::getline(ss, segment, ';') ) {
        game.push_back(segment);
    }

    return game;
}

std::vector<std::vector<cubes>> parse(const std::string& input_path)
{
    std::vector<std::vector<cubes>> allCubes;

    for ( auto& line : get_input(input_path) ) {
        allCubes.push_back(parseGame(line.substr(line.find(":") + 2)));
    }

    return allCubes;
}

template <>
void solution<2>::part1(const std::string& input_path)
{
    const auto games = parse(input_path);
    const cubes MAX_CUBES = { 12, 13, 14 };

    int result = 0;
    for ( int i = 0; i < games.size(); ++i ) {
        bool valid = std::all_of(games[i].begin(), games[i].end(), [&MAX_CUBES] (const cubes& c) {
            return c.r <= MAX_CUBES.r && c.g <= MAX_CUBES.g && c.b <= MAX_CUBES.b;
        });

        if ( valid )
            result += i + 1;
    }

    const int expected_solution = 2600;
    print_solution(result, expected_solution);
}

template <>
void solution<2>::part2(const std::string& input_path)
{
    const auto games = parse(input_path);

    int result = 0;
    for ( int i = 0; i < games.size(); ++i ) {
        cubes min = { -1, -1, -1 };
        std::for_each(games[i].begin(), games[i].end(), [&min] (const cubes& c) {
            min.r = std::max(min.r, c.r);
            min.g = std::max(min.g, c.g);
            min.b = std::max(min.b, c.b);
        });

        result += (min.r * min.g * min.b);
    }

    const int expected_solution = 86036;
    print_solution(result, expected_solution);
}
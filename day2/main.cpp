#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

struct cubes {
    int r, g, b;
};

void print(const std::vector<cubes>& cubes)
{
    for ( const auto& cubes : cubes )
    {
        std::cout << "r: " << cubes.r << " g: " << cubes.g << " b: " << cubes.b << "\n";
    }
}

std::vector<cubes> parseGame(const std::string& line)
{
    const std::map<std::string, int cubes::*> colorMap = { {"red", &cubes::r}, {"green", &cubes::g}, {"blue", &cubes::b} };
    std::vector<cubes> game;
    std::istringstream ss(line);
    std::string segment;

    while ( std::getline(ss, segment, ';') )
    {
        cubes c = { 0, 0, 0 };
        std::istringstream segmentStream(segment);
        int quantity;
        std::string color;

        while ( segmentStream >> quantity >> color )
        {
            if ( color.back() == ',' )
                color.pop_back();

            auto it = colorMap.find(color);
            if ( it != colorMap.end() )
            {
                c.*it->second += quantity;
            }
        }
        game.push_back(c);
    }

    return game;
}

std::vector<std::vector<cubes>> parse(const std::string& filename)
{
    std::fstream file(filename, std::ios::in);

    if ( !file.is_open() )
    {
        std::cout << "failed to open file\n";
        return {};
    }

    std::vector<std::vector<cubes>> allCubes;
    std::string line;

    while ( std::getline(file, line) )
    {
        size_t startPos = line.find(":") + 2;
        if ( startPos != std::string::npos )
        {
            std::string gameData = line.substr(startPos);
            allCubes.push_back(parseGame(gameData));
        }
    }

    return allCubes;
}

void p1(const std::vector<std::vector<cubes>>& games)
{
    const cubes MAX_CUBES = { .r = 12, .g = 13, .b = 14 };
    int sum = 0;

    for ( int i = 0; i < games.size(); ++i )
    {
        bool valid = true;
        for ( const auto& cubes : games[i] )
        {
            valid &= (cubes.r <= MAX_CUBES.r && cubes.g <= MAX_CUBES.g && cubes.b <= MAX_CUBES.b);
        }

        if ( valid )
            sum += i + 1;
    }

    std::cout << "P1: " << sum << "\n";
}

void p2(const std::vector<std::vector<cubes>>& games)
{
    int sum = 0;

    for ( int i = 0; i < games.size(); ++i )
    {
        cubes min = { -1, -1, -1 };

        for ( const auto& cubes : games[i] )
        {
            min.r = std::max(min.r, cubes.r);
            min.g = std::max(min.g, cubes.g);
            min.b = std::max(min.b, cubes.b);
        }

        sum += (min.r * min.g * min.b);
    }

    std::cout << "P2: " << sum << "\n";
}

int main()
{
    const std::string filename = "input.txt";
    const auto allCubes = parse(filename);

    p1(allCubes);
    p2(allCubes);
}
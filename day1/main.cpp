#include <string>
#include <fstream>
#include <iostream>
#include <vector>

int part_one(std::fstream& fs)
{
    fs.clear();
    fs.seekg(0, std::ios::beg);

    std::string line;
    int res = 0;
    while ( fs >> line )
    {
        int n = line.size();
        int i;
        int val = 0;

        for ( i = 0; i < n && !(line[i] >= '0' && line[i] <= '9'); ++i ) { }
        val += 10 * (line[i] - '0');

        for ( i = n - 1; i >= 0 && !(line[i] >= '0' && line[i] <= '9'); --i ) { }
        val += (line[i] - '0');

        res += val;
    }

    fs.close();
    return res;
}

// pain, numbers can be concatenated :,)
std::string replace_nr(std::fstream& fs)
{
    fs.clear();
    fs.seekg(0, std::ios::beg);

    const std::vector <std::string> numbers = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
    const int numbers_size = numbers.size();
    const std::string file = "clean.txt";

    std::fstream clean(file, std::ios::out | std::ios::trunc);

    if ( !clean.is_open() )
    {
        std::cout << "failed opening file!\n";
        return "";
    }

    std::string line;

    while ( fs >> line )
    {
        for ( int i = 0; i < numbers_size; ++i )
        {
            size_t idx = 0;
            while ( (idx = line.find(numbers[i], idx)) != std::string::npos )
            {
                line.replace(++idx, 1, std::to_string(i + 1));
            }
        }

        clean << line << "\n";
    }

    fs.close();
    clean.close();
    return file;
}

int part_two(std::fstream& fs)
{
    std::string line;
    std::string file = replace_nr(fs);

    std::fstream clean(file);

    if ( !clean.is_open() )
    {
        std::cout << "failed opening file!\n";
        return -1;
    }

    int res = part_one(clean);
    clean.close();
    return res;
}

int main()
{
    const std::string file = "input.txt";
    std::fstream fs(file, std::ios::in);

    if ( !fs.is_open() )
    {
        std::cout << "failed opening file!\n";
        return -1;
    }

    std::cout << "part one: " << part_one(fs) << "\n";

    fs.close();
    fs.open(file, std::ios::in);

    std::cout << "part two: " << part_two(fs) << "\n";
    fs.close();
}
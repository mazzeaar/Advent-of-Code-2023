#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <set>

using schema = std::vector<std::vector<char>>;

inline bool is_symbol(char s)
{
    return s != '.' && !isdigit(s);
}

// inefficient but idc
bool is_part(const schema& s, int row, int col, int nsize)
{
    for ( int i = 0; i < nsize; ++i )
    {
        int currentCol = col + i;

        for ( int dr = -1; dr <= 1; ++dr )
        {
            for ( int dc = -1; dc <= 1; ++dc )
            {
                if ( dr == 0 && dc == 0 ) continue;

                int checkRow = row + dr;
                int checkCol = currentCol + dc;

                if ( checkRow >= 0 && checkRow < s.size() &&
                    checkCol >= 0 && checkCol < s[0].size() &&
                    is_symbol(s[checkRow][checkCol]) )
                {
                    return true;
                }
            }
        }
    }
    return false;
}

schema getinput(const std::string& path)
{
    schema input;
    std::string line;
    std::ifstream file(path);

    if ( !file.is_open() )
    {
        std::cout << "Failed to open file\n";
        return {};
    }

    while ( std::getline(file, line) )
    {
        std::vector<char> cline(line.begin(), line.end());
        input.push_back(cline);
    }

    return input;
}

void p1(const std::string& path)
{
    schema input = getinput(path);

    if ( input.empty() )
    {
        std::cout << "No input data found.\n";
        return;
    }

    unsigned long long sum = 0;
    const int h = input.size();
    const int w = input[0].size();

    for ( int r = 0; r < h; ++r )
    {
        for ( int c = 0; c < w; ++c )
        {
            if ( isdigit(input[r][c]) )
            {
                int nsize = 0;
                for ( int i = c; i < w && isdigit(input[r][i]); ++i )
                {
                    nsize++;
                }

                if ( is_part(input, r, c, nsize) )
                {
                    int number = 0;
                    for ( int i = c; i < c + nsize; ++i )
                    {
                        number = number * 10 + (input[r][i] - '0');
                    }
                    sum += number;
                }

                c += nsize - 1;
            }
        }
    }

    std::cout << "p1: " << sum << "\n";
}

unsigned long long gear_ratio(const schema& s, int r, int c)
{
    std::set<int> unique_parts;

    for ( int dr = -1; dr <= 1; ++dr )
    {
        for ( int dc = -1; dc <= 1; ++dc )
        {
            if ( dr == 0 && dc == 0 ) continue;

            int checkRow = r + dr, checkCol = c + dc;
            if ( checkRow < 0 || checkRow >= s.size() || checkCol < 0 || checkCol >= s[0].size() ) continue;

            if ( isdigit(s[checkRow][checkCol]) && is_part(s, checkRow, checkCol, 1) )
            {
                int startCol = checkCol;
                while ( startCol > 0 && isdigit(s[checkRow][startCol - 1]) ) startCol--;

                int number = 0;
                for ( int i = startCol; i < s[0].size() && isdigit(s[checkRow][i]); ++i )
                {
                    number = number * 10 + (s[checkRow][i] - '0');
                }

                unique_parts.insert(number);
            }
        }
    }

    return unique_parts.size() == 2 ? *unique_parts.begin() * *(++unique_parts.begin()) : 0;
}

void p2(const std::string& path)
{
    schema input = getinput(path);
    unsigned long long total_gear_ratio = 0;
    const int h = input.size();
    const int w = input[0].size();

    for ( int r = 0; r < h; ++r )
    {
        for ( int c = 0; c < w; ++c )
        {
            if ( input[r][c] == '*' )
            {
                unsigned long long ratio = gear_ratio(input, r, c);
                total_gear_ratio += ratio;
            }
        }
    }

    std::cout << "p2: " << total_gear_ratio << "\n";
}


int main()
{
    const std::string path = "input.txt";
    p1(path);
    p2(path);
}

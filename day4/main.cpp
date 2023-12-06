#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <cmath>

struct card {
    std::set<int> winning;
    std::set<int> deck;

    int inter_size()
    {
        std::vector<int> inters;
        std::set_intersection(winning.begin(), winning.end(), deck.begin(), deck.end(), std::back_inserter(inters));

        return inters.size();
    }
};

void print(const card& c)
{
    std::cout << "w: ";
    for ( const auto& i : c.winning ) std::cout << i << ' ';

    std::cout << "d: ";
    for ( const auto& i : c.deck ) std::cout << i << ' ';

    std::cout << '\n';
}

void print(const std::vector<card>& cards) { for ( const auto& c : cards ) print(c); }

std::vector<card> input(const std::string& path)
{
    std::fstream file(path, std::ios::in);
    if ( !file.is_open() )
    {
        std::cout << "Failed to open file\n";
        return {};
    }

    std::string line;
    std::vector<card> cards;
    while ( std::getline(file, line) )
    {
        int num = 0;
        card c;

        std::stringstream ws(line.substr(line.find(':') + 1, line.find('|')));
        while ( ws >> num )
            c.winning.insert(num);

        std::stringstream ds(line.substr(line.find('|') + 1));
        while ( ds >> num )
            c.deck.insert(num);

        cards.push_back(c);
    }

    return cards;
}

void p1(const std::string& path)
{
    auto cards = input(path);
    int sum = 0;

    for ( auto& c : cards )
    {
        int s = c.inter_size();
        if ( s != 0 )
            sum += std::pow(2, s - 1);
    }

    std::cout << "p1: " << sum << '\n';
}

void p2(const std::string& path)
{
    auto cards = input(path);
    std::vector<int> copies(cards.size(), 1);

    const int n = cards.size();
    for ( int i = 0; i < n; ++i )
    {
        int s = cards[i].inter_size();

        if ( s != 0 )
            for ( int j = i+1; j < i + 1 + s; ++j )
                copies[j] += copies[i];
    }

    int res = 0;
    for ( const auto& c : copies )
        res += c;

    std::cout << "p2: " << res << '\n';
}

int main()
{
    const std::string file = "input.txt";
    p1(file);
    p2(file);
}
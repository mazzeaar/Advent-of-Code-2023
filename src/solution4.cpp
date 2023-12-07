#include "../include/solution.h"

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

std::vector<card> input(const std::string& path)
{
    std::fstream file(path, std::ios::in);
    if ( !file.is_open() ) {
        std::cout << "Failed to open file\n";
        return {};
    }

    std::string line;
    std::vector<card> cards;
    while ( std::getline(file, line) ) {
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

template <>
void solution<4>::part1(const std::string& input_path)
{
    auto cards = input(input_path);

    int solution = 0;
    for ( auto& c : cards ) {
        int s = c.inter_size();
        if ( s != 0 )
            solution += std::pow(2, s - 1);
    }

    const int expected_solution = 24175;
    print_solution(solution, expected_solution);
}

template <>
void solution<4>::part2(const std::string& input_path)
{
    auto cards = input(input_path);
    std::vector<int> copies(cards.size(), 1);

    const int n = cards.size();
    for ( int i = 0; i < n; ++i ) {
        int s = cards[i].inter_size();

        if ( s != 0 )
            for ( int j = i+1; j < i + 1 + s; ++j )
                copies[j] += copies[i];
    }

    int solution = 0;
    for ( const auto& c : copies )
        solution += c;

    const int expected_solution = 18846301;
    print_solution(solution, expected_solution);
}
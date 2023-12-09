#include "../include/solution.h"

struct card {
    std::set<int> winning;
    std::set<int> deck;

    card(std::string& line)
    {
        std::istringstream iss(line.substr(line.find(':') + 1, line.find('|') - 1));
        winning = std::set<int>(std::istream_iterator<int>(iss), std::istream_iterator<int>());

        std::istringstream is(line.substr(line.find('|') + 1));
        deck = std::set<int>(std::istream_iterator<int>(is), std::istream_iterator<int>());
    }

    inline int inter_size()
    {
        std::vector<int> inters;
        std::set_intersection(winning.begin(), winning.end(), deck.begin(), deck.end(), std::back_inserter(inters));
        return inters.size();
    }
};

std::vector<card> input(const std::string& path)
{
    std::vector<card> cards;

    for ( auto& line : get_input(path) ) {
        cards.push_back(line);
    }

    return cards;
}

template <>
void solution<4>::part1(const std::string& input_path)
{
    int solution = 0;
    for ( auto& c : input(input_path) ) {
        int s = c.inter_size();
        if ( s != 0 ) solution += std::pow(2, s - 1);
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
    int s;
    for ( int i = 0; i < n; ++i ) {
        if ( (s = cards[i].inter_size()) == 0 )
            continue;

        for ( int j = i+1; j < i + 1 + s; ++j )
            copies[j] += copies[i];
    }

    const int expected_solution = 18846301;
    print_solution(std::accumulate(copies.begin(), copies.end(), 0), expected_solution);
}
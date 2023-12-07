#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

enum hand_type {
    high_card = 0,
    one_pair,
    two_pair,
    three_of_a_kind,
    full_house,
    four_of_a_kind,
    five_of_a_kind
};

hand_type get_type_p1(const std::string& hand)
{
    std::map<char, int> card_count;
    for ( char card : hand ) {
        card_count[card]++;
    }

    int pairs = 0;
    bool three = false, four = false, five = false;

    for ( auto const& pair : card_count ) {
        if ( pair.second == 2 ) pairs++;
        else if ( pair.second == 3 ) three = true;
        else if ( pair.second == 4 ) four = true;
        else if ( pair.second == 5 ) five = true;
    }

    if ( five ) return five_of_a_kind;
    else if ( four ) return four_of_a_kind;
    else if ( three && pairs == 1 ) return full_house;
    else if ( three ) return three_of_a_kind;
    else if ( pairs == 2 ) return two_pair;
    else if ( pairs == 1 ) return one_pair;
    else return high_card;
}

hand_type get_type_p2(const std::string& hand)
{
    hand_type type1 = get_type_p1(hand);

    int jokers = 0;
    for ( char card : hand ) {
        if ( card == 'J' ) ++jokers;
    }

    if ( jokers == 0 ) return type1;

    if ( jokers == 1 ) {
        if ( type1 == high_card ) return one_pair;
        if ( type1 == one_pair ) return three_of_a_kind;
        if ( type1 == two_pair ) return full_house;
        if ( type1 == three_of_a_kind ) return four_of_a_kind;
        if ( type1 == full_house ) return four_of_a_kind;
        if ( type1 == four_of_a_kind ) return five_of_a_kind;
    }

    if ( jokers == 2 ) {
        if ( type1 == one_pair ) return three_of_a_kind;
        if ( type1 == two_pair ) return four_of_a_kind;
        if ( type1 == full_house ) return five_of_a_kind;
    }

    if ( jokers == 3 ) {
        if ( type1 == three_of_a_kind ) return four_of_a_kind;
        if ( type1 == full_house ) return five_of_a_kind;
    }

    if ( jokers == 4 ) {
        if ( type1 == four_of_a_kind ) return five_of_a_kind;
    }
}

struct input {
    std::string hand;
    int bid;

    input(const std::string& in)
        : hand(in.substr(0, in.find(" "))),
        bid(std::stoi(in.substr(in.find(" ") + 1)))
    { }

    friend std::ostream& operator<<(std::ostream& os, const input& in)
    {
        return os << in.hand << " " << in.bid;
    }

    bool comparator_p1(const input& rhs) const
    {
        hand_type lhs_type = get_type_p1(hand);
        hand_type rhs_type = get_type_p1(rhs.hand);
        if ( lhs_type != rhs_type ) return lhs_type < rhs_type;

        const static std::string card_val = "23456789TJQKA";
        for ( int i = 0; i < hand.size(); ++i ) {
            if ( hand[i] == rhs.hand[i] ) continue;
            return card_val.find(hand[i]) < card_val.find(rhs.hand[i]);
        }

        return false;
    }

    bool comparator_p2(const input& rhs) const
    {
        hand_type lhs_type = get_type_p2(hand);
        hand_type rhs_type = get_type_p2(rhs.hand);
        if ( lhs_type != rhs_type ) return lhs_type < rhs_type;

        const static std::string card_val = "23456789TJQKA";
        for ( int i = 0; i < hand.size(); ++i ) {
            if ( hand[i] == rhs.hand[i] ) continue;
            return card_val.find(hand[i]) < card_val.find(rhs.hand[i]);
        }

        return false;
    }
};

std::vector<input> get_input(const std::string& path)
{
    std::fstream file(path, std::ios::in);
    if ( !file.is_open() ) {
        std::cout << "failed to open file\n";
        return {};
    }

    std::vector<input> inputs;
    std::string line;
    while ( std::getline(file, line) ) {
        inputs.emplace_back(line);
    }

    return inputs;
}

void p1(const std::string& path)
{
    auto inputs = get_input(path);

    std::sort(inputs.begin(), inputs.end(), [ ] (const input& lhs, const input& rhs) {
        return lhs.comparator_p1(rhs);
    });

    long long sum = 0;
    int n = inputs.size();
    for ( int i = n-1; i >= 0; --i ) {
        sum += (i+1) * inputs[i].bid;
    }

    if ( sum != 250232501 )
        std::cout << "wrong answer\n";
    else
        std::cout << "p1: " << sum << '\n';
}

void p2(const std::string& path)
{
    auto inputs = get_input(path);

    std::sort(inputs.begin(), inputs.end(), [ ] (const input& lhs, const input& rhs) {
        return lhs.comparator_p2(rhs);
    });

    long long sum = 0;
    int n = inputs.size();
    for ( int i = n-1; i >= 0; --i ) {
        sum += (i+1) * inputs[i].bid;
    }

    std::cout << "p2: " << sum;
    if ( sum <= 248845051 ) {
        std::cout << " too low";
    }
    else if ( sum >= 249292613 ) {
        std::cout << " too high";
    }
    else if ( sum == 249256823 ) {
        std::cout << " wrong";
    }
    else if ( sum == 249242039 ) {
        std::cout << " wrong";
    }

    std::cout << '\n';
}

int main()
{
    const std::string input = "input.txt";
    p1(input);
    p2(input);
}


/*
std::map<char, int> card_count;
    for ( char card : hand ) {
        card_count[card]++;
    }

    int jokers = card_count['J'];
    if ( jokers == 0 ) return get_type_p1(hand);
    else if ( jokers == 5 || jokers == 4 ) {
        return five_of_a_kind;
    }

    int pairs = 0;
    bool three = false, four = false, five = false;

    for ( auto const& pair : card_count ) {
        if ( pair.first == 'J' ) {
            continue;
        }
        else if ( pair.second == 2 ) pairs++;
        else if ( pair.second == 3 ) three = true;
        else if ( pair.second == 4 ) four = true;
    }


    if ( jokers == 3 ) {
        if ( pairs == 1 ) return five_of_a_kind;
        else return four_of_a_kind;
    }
    else if ( jokers == 2 ) {
        if ( three ) return five_of_a_kind;
        else if ( pairs == 1 ) return four_of_a_kind;
        else return three_of_a_kind;
    }
    else {
        if ( four ) return five_of_a_kind;
        else if ( three ) return four_of_a_kind;
        else if ( pairs == 2 ) return full_house;
        else if ( pairs == 1 ) return three_of_a_kind;
        else return one_pair;
    }
*/
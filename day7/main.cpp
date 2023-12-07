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
    std::for_each(hand.begin(), hand.end(), [&card_count] (char card) {
        card_count[card]++;
    });

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
    std::map<char, int> card_count;
    std::for_each(hand.begin(), hand.end(), [&card_count] (char card) {
        card_count[card]++;
    });

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
}

struct Input {
    std::string hand;
    int bid;

    Input(const std::string& in)
        : hand(in.substr(0, in.find(" "))),
        bid(std::stoi(in.substr(in.find(" ") + 1)))
    { }

    bool comparator_p1(const Input& rhs) const
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

    bool comparator_p2(const Input& rhs) const
    {
        hand_type lhs_type = get_type_p2(hand);
        hand_type rhs_type = get_type_p2(rhs.hand);
        if ( lhs_type != rhs_type ) return lhs_type < rhs_type;

        const static std::string card_val = "J23456789TQKA";
        for ( int i = 0; i < hand.size(); ++i ) {
            if ( hand[i] == rhs.hand[i] ) continue;
            return card_val.find(hand[i]) < card_val.find(rhs.hand[i]);
        }

        return false;
    }
};

std::vector<Input> get_input(const std::string& path)
{
    std::fstream file(path, std::ios::in);
    if ( !file.is_open() ) {
        std::cout << "failed to open file\n";
        return {};
    }

    std::vector<Input> inputs;
    std::string line;
    while ( std::getline(file, line) )
        inputs.emplace_back(line);

    return inputs;
}

long long p1(std::vector<Input>& input)
{
    std::sort(input.begin(), input.end(), [ ] (const Input& lhs, const Input& rhs) {
        return lhs.comparator_p1(rhs);
    });

    long long sum = 0;
    int n = input.size();
    for ( int i = 0; i < n; ++i ) {
        sum += (i+1) * input[i].bid;
    }

    return sum;
}

long long p2(std::vector<Input>& input)
{
    std::sort(input.begin(), input.end(), [ ] (const Input& lhs, const Input& rhs) {
        return lhs.comparator_p2(rhs);
    });

    long long sum = 0;
    int n = input.size();
    for ( int i = 0; i < n; ++i ) {
        sum += (i+1) * input[i].bid;
    }

    return sum;
}

int main()
{
    const std::string input = "input.txt";
    std::vector<Input> inputs = get_input(input);
    long long ans1 = p1(inputs);
    long long ans2 = p2(inputs);

    if ( ans1 != 250232501 || ans2 != 249138943 ) {
        std::cout << "you fucked up\n";
        return 1;
    }

    std::cout << "p1: " << p1(inputs) << '\n';
    std::cout << "p2: " << p2(inputs) << '\n';
}
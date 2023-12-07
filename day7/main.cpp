#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>

enum hand_type {
    high_card = 0,
    one_pair,
    two_pair,
    three_of_a_kind,
    full_house,
    four_of_a_kind,
    five_of_a_kind
};

hand_type get_type(const std::string& hand, bool consider_jokers)
{
    std::unordered_map<char, int> card_count;
    for ( char card : hand ) {
        card_count[card]++;
    }

    int pairs = 0;
    bool four = false, three = false;
    for ( const auto& pair : card_count ) {
        switch ( pair.second ) {
        case 2: ++pairs; break;
        case 3: three = true; break;
        case 4: four = true; break;
        case 5: return five_of_a_kind;
        }
    }

    int jokers = consider_jokers ? card_count['J'] : 0;
    switch ( jokers ) {
    case 4:
        return five_of_a_kind;
    case 3:
        if ( pairs == 1 ) return five_of_a_kind;
        else return four_of_a_kind;
    case 2:
        if ( three ) return five_of_a_kind;
        else if ( pairs == 2 ) return four_of_a_kind;
        else return three_of_a_kind;
    case 1:
        if ( four ) return five_of_a_kind;
        else if ( three ) return four_of_a_kind;
        else if ( pairs == 2 ) return full_house;
        else if ( pairs == 1 ) return three_of_a_kind;
        else return one_pair;
    }

    if ( four ) return four_of_a_kind;
    else if ( three && pairs == 1 ) return full_house;
    else if ( three ) return three_of_a_kind;
    else if ( pairs == 2 ) return two_pair;
    else if ( pairs == 1 ) return one_pair;
    else return high_card;
}

struct Input {
    std::string hand;
    int bid;

    Input(const std::string& in)
        : hand(in.substr(0, in.find(" "))), bid(std::stoi(in.substr(in.find(" ") + 1)))
    { }

    bool comparator(const Input& rhs, bool consider_jokers) const
    {
        hand_type lhs_type = get_type(hand, consider_jokers), rhs_type = get_type(rhs.hand, consider_jokers);
        if ( lhs_type != rhs_type ) return lhs_type < rhs_type;

        const std::string card_val = consider_jokers ? "J23456789TJQKA" : "23456789TJQKA";
        for ( size_t i = 0; i < hand.size(); ++i ) {
            if ( hand[i] != rhs.hand[i] ) {
                return card_val.find(hand[i]) < card_val.find(rhs.hand[i]);
            }
        }

        return false;
    }
};

int compute_score(const std::vector<Input>& input)
{
    int sum = 0;
    for ( int i = 0; i < input.size(); ++i ) {
        sum += (i+1) * input[i].bid;
    }

    return sum;
}

int p1(std::vector<Input>& input)
{
    std::sort(input.begin(), input.end(), [ ] (const Input& lhs, const Input& rhs) {
        return lhs.comparator(rhs, false);
    });

    return compute_score(input);
}

int p2(std::vector<Input>& input)
{
    std::sort(input.begin(), input.end(), [ ] (const Input& lhs, const Input& rhs) {
        return lhs.comparator(rhs, true);
    });

    return compute_score(input);
}

int main()
{
    const std::string path = "input.txt";
    std::fstream file(path, std::ios::in);
    if ( !file.is_open() ) {
        std::cout << "failed to open file\n";
        return {};
    }

    std::vector<Input> inputs;
    std::string line;
    while ( std::getline(file, line) ) {
        inputs.emplace_back(line);
    }

    std::cout << "p1: " << p1(inputs) << '\n';
    std::cout << "p2: " << p2(inputs) << '\n';
}
#include "../include/solution.h"

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

template <>
void solution<7>::part1(const std::string& input_path)
{
    std::vector<std::string> file = get_input(input_path);

    std::vector<Input> parsed_input;
    for ( const auto& line : file ) {
        parsed_input.emplace_back(line);
    }

    std::sort(parsed_input.begin(), parsed_input.end(), [ ] (const Input& lhs, const Input& rhs) {
        return lhs.comparator(rhs, false);
        });

    int solution = compute_score(parsed_input);
    const int expected_solution = 250232501;

    print_solution(solution, expected_solution);
}

template <>
void solution<7>::part2(const std::string& input_path)
{
    std::vector<std::string> file = get_input(input_path);

    std::vector<Input> parsed_input;
    for ( const auto& line : file ) {
        parsed_input.emplace_back(line);
    }

    std::sort(parsed_input.begin(), parsed_input.end(), [ ] (const Input& lhs, const Input& rhs) {
        return lhs.comparator(rhs, true);
        });

    int solution = compute_score(parsed_input);
    const int expected_solution = 249138943;

    print_solution(solution, expected_solution);
}
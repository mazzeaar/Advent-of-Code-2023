#include "../include/solution.h"

using ll = long long;

struct race {
    ll time;    // s
    ll dist;    // m
};

ll nr_winning_ways(const race& race)
{
    ll winning_ways = 0;
    for ( ll hold_time = 0; hold_time < race.time; ++hold_time ) {
        if ( ((race.time - hold_time) * hold_time) > race.dist ) {
            ++winning_ways;
        }
    }

    return winning_ways;
}

// input is not needed for this day but its kept for consistency
template <>
void solution<6>::part1(const std::string& input_path)
{
    std::vector<std::string> file = get_input(input_path);
    std::vector<race> input = {
        {53, 275},
        {71, 1181},
        {78, 1215},
        {80, 1524}
    };

    ll solution = 1;
    for ( const auto& race : input )
        solution *= nr_winning_ways(race);

    const ll expected_solution = 449820;
    print_solution(solution, expected_solution);
}

// input is not needed for this day but its kept for consistency
template <>
void solution<6>::part2(const std::string& input_path)
{
    std::vector<std::string> file = get_input(input_path);

    race input = { 53717880, 275118112151524 };

    ll solution = nr_winning_ways(input);
    const ll expected_solution = 42250895;
    print_solution(solution, expected_solution);
}
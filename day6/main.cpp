#include <vector>
#include <iostream>

using ll = long long;

struct race {
    ll time;    // s
    ll dist;    // m
};

ll nr_winning_ways(const race& race)
{
    ll winning_ways = 0;
    for ( ll hold_time = 0; hold_time < race.time; ++hold_time )
    {
        if ( (race.time * hold_time) - (hold_time * hold_time) > race.dist )
        {
            ++winning_ways;
        }
    }

    return winning_ways;
}

int main()
{
    std::vector<race> p1 = {
        {53, 275},
        {71, 1181},
        {78, 1215},
        {80, 1524}
    };

    ll res_p1 = 1;
    for ( const auto& race : p1 )
        res_p1 *= nr_winning_ways(race);

    std::cout << "p1: " << res_p1 << '\n';

    race p2 = { 53717880, 275118112151524 };
    std::cout << "p2: " << nr_winning_ways(p2) << '\n';
}

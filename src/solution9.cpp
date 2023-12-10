#include "../include/solution.h"

template <bool backtrack>
long long extrapolateNextValue(const std::vector<long long>& sequence)
{
    std::vector<std::vector<long long>> sequences(1, sequence);

    // generate diff sequences
    while ( true ) {
        std::vector<long long> diffSequence;
        std::adjacent_difference(sequences.back().begin(), sequences.back().end(), std::back_inserter(diffSequence));
        diffSequence.erase(diffSequence.begin()); // first elem is always 0 and not a difference

        if ( std::all_of(diffSequence.begin(), diffSequence.end(), [ ] (long long n) { return n == 0; }) ) {
            break;
        }

        sequences.push_back(diffSequence);
    }

    for ( int i = sequences.size() - 2; i >= 0; --i ) {
        if constexpr ( backtrack ) {
            sequences[i].insert(sequences[i].begin(), sequences[i].front() - sequences[i + 1].front());
        }
        else {
            sequences[i].push_back(sequences[i].back() + sequences[i + 1].back());
        }
    }

    if constexpr ( backtrack ) {
        return sequences.front().front();
    }
    else {
        return sequences.front().back();
    }
}

template <>
void solution<9>::part1(const std::string& input_path)
{
    auto input = get_ll_input(input_path);
    long long result = std::accumulate(input.begin(), input.end(), 0LL, [ ] (long long acc, const auto& seq) {
        return acc + extrapolateNextValue<false>(seq);
    });

    const long long expected = 1969958987;
    print_solution(result, expected);
}

template <>
void solution<9>::part2(const std::string& input_path)
{
    auto input = get_ll_input(input_path);
    int result = std::accumulate(input.begin(), input.end(), 0LL, [ ] (long long acc, const auto& seq) {
        return acc + extrapolateNextValue<true>(seq);
    });

    const int expected = 1068;
    print_solution(result, expected);
}
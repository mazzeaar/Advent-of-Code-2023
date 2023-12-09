#include "../include/solution.h"

using ll = long long;

std::vector<std::vector<ll>> get_ll_input(const std::string& file_path)
{
    std::fstream input_file(file_path, std::ios::in);
    if ( !input_file.is_open() ) {
        throw std::runtime_error("COULD NOT OPEN FILE " + file_path);
    }

    std::vector<std::vector<ll>> input;
    std::string line;
    while ( std::getline(input_file, line) ) {
        std::istringstream iss(line);
        std::vector<ll> numbers((std::istream_iterator<ll>(iss)), std::istream_iterator<ll>());
        input.push_back(numbers);
    }

    return input;
}

template <bool backtrack>
ll extrapolateNextValue(const std::vector<ll>& sequence)
{
    std::vector<std::vector<ll>> sequences(1, sequence);

    // generate diff sequences
    while ( true ) {
        std::vector<ll> diffSequence;
        std::adjacent_difference(sequences.back().begin(), sequences.back().end(), std::back_inserter(diffSequence));
        diffSequence.erase(diffSequence.begin()); // first elem is always 0 and not a difference

        if ( std::all_of(diffSequence.begin(), diffSequence.end(), [ ] (ll n) { return n == 0; }) ) {
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

    ll result = std::accumulate(input.begin(), input.end(), 0LL, [ ] (ll acc, const auto& seq) {
        return acc + extrapolateNextValue<false>(seq);
    });

    const ll expected = 1969958987;
    print_solution(result, expected);
}

template <>
void solution<9>::part2(const std::string& input_path)
{
    auto input = get_ll_input(input_path);

    ll result = std::accumulate(input.begin(), input.end(), 0LL, [ ] (ll acc, const auto& seq) {
        return acc + extrapolateNextValue<true>(seq);
    });

    const ll expected = 1068;
    print_solution(result, expected);
}
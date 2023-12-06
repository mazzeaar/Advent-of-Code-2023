#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>

using ll = long long;

struct Range {
    ll start;
    ll length;

    inline bool contains(ll value) const { return value >= start && value < start + length; }
    inline bool intersects(const Range& range) const { return range.start < start + length && range.start + range.length > start; }

    Range intersect(const Range& range) const
    {
        ll startOffset = std::max(range.start, start) - start;
        ll endOffset = std::min(range.start + range.length, start + length) - start;
        return { start + startOffset, endOffset - startOffset };
    }
};

struct MapEntry {
    Range source;
    Range dest;

    MapEntry() = default;
    MapEntry(Range src, Range dst) : source(src), dest(dst) { }

    inline bool canMap(const Range& range) const { return source.intersects(range); }

    Range mapRange(const Range& range) const
    {
        Range intersection = source.intersect(range);
        return { dest.start + intersection.start - source.start, intersection.length };
    }
};

struct Map {
    std::vector<MapEntry> entries;

    std::vector<Range> map(const Range& range) const
    {
        std::vector<Range> result;
        for ( const auto& entry : entries )
        {
            if ( entry.canMap(range) )
            {
                result.push_back(entry.mapRange(range));
            }
        }

        return result;
    }
};

std::vector<Map> getMaps(const std::string& filePath)
{
    std::ifstream file(filePath);
    if ( !file.is_open() )
    {
        std::cerr << "failed to open file\n";
        return {};
    }

    std::string line;
    std::vector<Map> maps;
    while ( std::getline(file, line) )
    {
        if ( line.find("map:") != std::string::npos )
        {
            Map map;
            while ( std::getline(file, line) && !line.empty() )
            {
                std::istringstream entryStream(line);
                MapEntry entry;
                entryStream >> entry.dest.start >> entry.source.start >> entry.source.length;
                map.entries.push_back(entry);
            }

            maps.push_back(map);
        }
    }

    return maps;
}

std::vector<ll> getSeeds(const std::string& path)
{
    std::ifstream file(path);
    if ( !file.is_open() )
    {
        std::cerr << "failed to open file\n";
        return {};
    }

    std::string line;
    while ( getline(file, line) && line.find("seeds:") == std::string::npos );

    ll seed;
    std::vector<ll> seeds;
    std::istringstream seedStream(line.substr(line.find(':') + 2));
    while ( seedStream >> seed )
    {
        seeds.push_back(seed);
    }

    return seeds;
}

void p1(const std::string& path)
{
    std::vector<ll> seeds = getSeeds(path);
    std::vector<Map> maps = getMaps(path);

    ll min_loc = std::numeric_limits<ll>::max();

    for ( const auto& seed : seeds )
    {
        Range currentRange = { seed, 1 };
        for ( const auto& map : maps )
        {
            std::vector<Range> mappedRanges = map.map(currentRange);
            if ( mappedRanges.empty() )
            {
                break;
            }

            currentRange = mappedRanges[0];
        }

        min_loc = std::min(min_loc, currentRange.start);
    }

    std::cout << "p1: " << min_loc << "\n";
}

void p2(const std::string& path)
{
    std::vector<ll> seeds = getSeeds(path);
    std::vector<Map> maps = getMaps(path);

    ll min_loc = std::numeric_limits<ll>::max();

    for ( int i = 0; i < seeds.size(); i += 2 )
    {
        Range currentRange = { seeds[i], seeds[i + 1] };
        std::vector<Range> currentRanges = { currentRange };

        for ( const auto& map : maps )
        {
            std::vector<Range> newRanges;
            for ( const auto& range : currentRanges )
            {
                auto mappedRanges = map.map(range);
                newRanges.insert(newRanges.end(), mappedRanges.begin(), mappedRanges.end());
            }
            currentRanges = newRanges;
        }

        for ( const auto& range : currentRanges )
        {
            min_loc = std::min(min_loc, range.start);
        }
    }

    std::cout << "p2: " << min_loc << "\n";
}

int main()
{
    const std::string filePath = "input.txt";
    p1(filePath);
    p2(filePath);
}
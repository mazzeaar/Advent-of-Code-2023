#include "../include/solution.h"

const int MAX_NODES = 750;

struct Node {
    int id;
    Node* left;
    Node* right;

    Node(int id) : id(id), left(nullptr), right(nullptr) { }
};

struct Input8 {
    std::string directions;
    std::vector<Node> nodes;
    std::unordered_map<std::string, int> nameToIdMap;
    std::vector<std::string> idToNameMap;

    int getNodeID(const std::string& name)
    {
        if ( nameToIdMap.find(name) == nameToIdMap.end() ) {
            int newId = nameToIdMap.size();
            nameToIdMap[name] = newId;
            idToNameMap.push_back(name);
            nodes.emplace_back(newId);
        }
        return nameToIdMap[name];
    }

    void parse_input(const std::vector<std::string>& input)
    {
        directions = input[0];
        nodes.reserve(MAX_NODES);
        for ( int i = 2; i < input.size(); ++i ) {
            std::string line = input[i];

            int nodeId = getNodeID(line.substr(0, 3));
            int leftId = getNodeID(line.substr(7, 3));
            int rightId = getNodeID(line.substr(12, 3));

            nodes[nodeId].left = &nodes[leftId];
            nodes[nodeId].right = &nodes[rightId];
        }
    }
};

template <>
void solution<8>::part1(const std::string& input_path)
{
    auto input = get_input(input_path);
    Input8 parsedInput;
    parsedInput.parse_input(input);

    int steps = 0;
    int startNodeId = parsedInput.getNodeID("AAA");
    int endNodeId = parsedInput.getNodeID("ZZZ");
    Node* currentNode = &parsedInput.nodes[startNodeId];
    int dirIndex = 0;

    while ( currentNode->id != endNodeId ) {
        char dir = parsedInput.directions[dirIndex % parsedInput.directions.size()];
        currentNode = (dir == 'L') ? currentNode->left : currentNode->right;

        ++steps;
        ++dirIndex;
    }

    const int expected = 17141;
    print_solution(steps, expected);
}
#include "../../graph.hpp"

using namespace lasd;

double Heuristic (const char& source, const int& dest) {
    double val = 0.0;
    switch(source) {
        case 'A':
            val = 5.0;
            break;
        case 'B':
            val = 4.0;
            break;
        case 'C':
            val = 4.0;
            break;
        case 'D':
            val = 3.0;
            break;
        case 'E':
            val = 3.0;
            break;
        case 'F':
            val = 1.0;
            break;
    }
    return val;
};

int main(int argc, char** argv) {
    DirectedGraph<char> graph;
    graph.addNode('A');
    graph.addNode('B');
    graph.addNode('C');
    graph.addNode('D');
    graph.addNode('E');
    graph.addNode('F');
    graph.addNode('G');

    graph.addEdge('A', 'B', 1.0);
    graph.addEdge('A', 'C', 4.0);
    graph.addEdge('B', 'C', 2.0);
    graph.addEdge('C', 'E', 5.0);
    graph.addEdge('E', 'G', 3.0);
    graph.addEdge('B', 'D', 3.0);
    graph.addEdge('D', 'G', 4.0);
    graph.addEdge('D', 'F', 2.0);
    graph.addEdge('F', 'G', 1.0);

    std::vector<std::pair<char, double>> path = graph.AStar('A', 'G', Heuristic);

    std::cout << "[A* SEARCH ALGORITHM FROM A TO G] RESULT: ";
    for (const auto& [node, fScore] : path) {
        std::cout << "{ Node: " << node << ", Heuristic: " << fScore << "} ";
    }
    std::cout << std::endl;
    return 0;
}
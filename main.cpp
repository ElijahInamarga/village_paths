#include <iostream>
#include "graph.h"

int main() {
    Graph graph;

    // Load the graph from input file
    if (!graph.loadGraphFromFile("input.txt")) {
        std::cerr << "Error loading graph from file." << std::endl;
        return 1;
    }

    // Execute Prim's algorithm
    std::vector<int> mstStart, mstEnd;
    int totalCost = graph.primMST(mstStart, mstEnd);

    // Print the MST and total cost
    std::cout << "Minimum Spanning Tree:" << std::endl;
    for (size_t i = 0; i < mstStart.size(); ++i) {
        std::cout << "Connecting village " << mstStart[i] << " to village " << mstEnd[i] << std::endl;
    }
    std::cout << "Total Cost: " << totalCost << std::endl;

    return 0;
}
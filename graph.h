#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <limits>

class Graph {
public:
    // Load the graph from a file
    bool loadGraphFromFile(const std::string& filename);

    // Prim's algorithm to find MST
    int primMST(std::vector<int>& mstStart, std::vector<int>& mstEnd);

private:
    int numNodes; // Number of nodes
    std::vector<std::vector<int>> adjMatrix; // Adjacency matrix
    const int INF = std::numeric_limits<int>::max(); // Infinity for no connection
};

#endif // GRAPH_H
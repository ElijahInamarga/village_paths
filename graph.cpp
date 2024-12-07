#include "graph.h"
#include <fstream>
#include <iostream>

// Load the graph from a file
bool Graph::loadGraphFromFile(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        return false;
    }

    int numEdges;
    infile >> numNodes >> numEdges;

    // Initialize 2-D vector size
    for(int i = 0; i < numEdges; i++) {
        std::vector<int> temp(numEdges); 
        adjMatrix.push_back(temp);
    }

    // Implement the adjacency matrix setup
    for(int i = 0; i < numEdges; i++) {
        int vertex1, vertex2, weight;
        infile >> vertex1 >> vertex2 >> weight;
        adjMatrix[vertex1 - 1][vertex2 - 1] = weight; // vertex - 1 b/c input.txt uses index starting with 1 instead of 0
    }

    // DELETE LATER!!!
    // Print adjacency matrix 
    for(int i = 0; i < adjMatrix.size(); i++) {
        for(int j = 0; j < adjMatrix[i].size(); j++) {
            std::cout << adjMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
    // Comment this line before submission
    //std::cout << "TODO: Implement adjacency matrix initialization here.\n";

    infile.close();
    return true;
}

// Prim's algorithm to find the MST
int Graph::primMST(std::vector<int>& mstStart, std::vector<int>& mstEnd) {
    // Placeholder for visited nodes and minimum weight initialization
    std::cout << "TODO: Implement Prim's algorithm here.\n";

    // Steps:
    // 1. Initialize visited array and minWeight array
    int visitedArray[numNodes];
    std::vector<int> minWeight;
    // 2. Start from node 1
    


    // 3. Use a loop to find the minimum weight edge at each step
    // 4. Update MST edges (mstStart and mstEnd vectors)
    // 5. Return the total cost of the MST

    // Placeholder output
    mstStart.push_back(1);
    mstEnd.push_back(2);
    std::cout << "TODO: Replace placeholder MST output with the actual MST.\n";

    return 0; // TODO: Return the actual total cost of the MST
}
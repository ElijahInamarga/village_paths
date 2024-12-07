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
    for(int i = 0; i < numNodes; i++) {
        std::vector<int> temp(numNodes); 
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
    for(int i = 0; i < numNodes; i++) {
        for(int j = 0; j < numNodes; j++) {
            std::cout << adjMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
    // Comment this line before submission
    //std::cout << "TODO: Implement adjacency matrix initialization here.\n";

    infile.close();
    return true;
}

/*
* Edge object:
* Node1 -- node of origin
* Node2 -- destination node
*/
struct Edge {
    int node1, node2, weight;
};

std::vector<Edge> heapify(std::vector<Edge> arr) {
    for (int i = arr.size() / 2 - 1; i >= 0; i--) {
        int current = i;
        int original;
        do {
            original = current;
            int smallest = original;
            int lChild = current * 2 + 1;
            int rChild = current * 2 + 2;

            // Find the smallest of the current, left, and right child
            if (lChild < arr.size() && arr[lChild].weight < arr[smallest].weight)
                smallest = lChild;
            if (rChild < arr.size() && arr[rChild].weight < arr[smallest].weight)
                smallest = rChild;

            if (smallest != current) {
                std::swap(arr[current], arr[smallest]);
                current = smallest;
            }
        } while (current != original);
    }

    return arr;
}

std::vector<Edge> heapSort(std::vector<Edge> arr) {
    const int originalSize = arr.size();
    int n = arr.size();
    
    arr = heapify(arr);
    std::vector<Edge> temp(originalSize);

    // Step 2: Extract elements from the heap one by one
    while (n > 0) {
        temp[originalSize - n] = arr[0];
        std::swap(arr[0], arr[n - 1]);
        n--; // Reduce heap size

        int current = 0;
        int original;
        do {
            original = current;
            int smallest = original;
            int lChild = current * 2 + 1;
            int rChild = current * 2 + 2;

            // Find the smallest
            if (lChild < n && arr[lChild].weight < arr[smallest].weight)
                smallest = lChild;
            if (rChild < n && arr[rChild].weight < arr[smallest].weight)
                smallest = rChild;

            if (smallest != current) {
                std::swap(arr[current], arr[smallest]);
                current = smallest;
            }
        } while (current != original);
    }

    return temp;
}

// Prim's algorithm to find the MST
int Graph::primMST(std::vector<int>& mstStart, std::vector<int>& mstEnd) {
    // Placeholder for visited nodes and minimum weight initialization
    std::cout << "TODO: Implement Prim's algorithm here.\n";

    // Steps:

    // 1. Initialize visited array and minWeight array
    int visitedArray[numNodes];
    std::vector<Edge> minWeight;

    // 2. Start from node 1
    int vertex = 1;

    // Adds all of node's edges into minWeight
    for(int i = 0; i < adjMatrix[0].size(); i++) {
        if(adjMatrix[vertex - 1][i] != 0) {
            Edge tempEdge;
            tempEdge.node1 = vertex;
            tempEdge.node2 = i + 1 ;
            tempEdge.weight = adjMatrix[vertex - 1][i];
            minWeight.push_back(tempEdge);
        }
    }

    // Sort minWeight
    minWeight = heapSort(minWeight);
    for(int i = 0; i < minWeight.size(); i++) {
        std::cout << minWeight[i].node1 << minWeight[i].node2 << minWeight[i].weight << std::endl;
    }

    // 3. Use a loop to find the minimum weight edge at each step
    // 4. Update MST edges (mstStart and mstEnd vectors)
    // 5. Return the total cost of the MST

    // Placeholder output
    mstStart.push_back(1);
    mstEnd.push_back(2);
    std::cout << "TODO: Replace placeholder MST output with the actual MST.\n";

    return 0; // TODO: Return the actual total cost of the MST
}
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
        std::vector<int> temp(numNodes, INF); 
        adjMatrix.push_back(temp);
    }

    // Cost to travel to same village is 0
    for(int i = 0; i < numNodes; i++) {
        adjMatrix[i][i] = 0;
    }

    // Implement the adjacency matrix setup
    for(int i = 0; i < numEdges; i++) {
        int vertex1 = INF, vertex2 = INF, weight = INF;
        infile >> vertex1 >> vertex2 >> weight;

        // Check for missing edges or weights
        if(vertex1 == INF || vertex2 == INF || weight == INF) {
            std::cerr << "Error: missing edges or weights when loading graph from file" << std::endl;
            return false;
        }

        adjMatrix[vertex1 - 1][vertex2 - 1] = weight; // vertex - 1 b/c input.txt uses index starting with 1 instead of 0
        adjMatrix[vertex2 - 1][vertex1 - 1] = weight; // The graph is undirected
    }

    // Print adjMatrix
    // for(int i = 0; i < adjMatrix.size(); i++) {
    //     for(int j = 0; j < adjMatrix[0].size(); j++) {
    //         if(adjMatrix[i][j] == INF) {
    //             std::cout << "I" << " ";
    //             continue;
    //         }
    //         std::cout << adjMatrix[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

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
    // Build the heap using upheap
    int arrSize = arr.size();
    for(int i = 0; i < arrSize; i++) {
        int current = i;
        int parent = (current - 1) / 2;
        while(current != 0 && arr[current].weight < arr[parent].weight) {
            std::swap(arr[current], arr[parent]);
            current = parent;
            parent = (current - 1) / 2;
        }
    }
    return arr;
}

// Main function to perform heap sort on the array
std::vector<Edge> heapSort(std::vector<Edge> arr) {
    // Step 1: Build a min-heap
    arr = heapify(arr);

    const int originalSize = arr.size();
    std::vector<Edge> temp(originalSize);
    int n = arr.size();

    while(n > 0) {
        // Step 2: Extract elements from the heap one by one
        temp[originalSize - n] = arr[0];
        std::swap(arr[0], arr[n - 1]);
        n--;

        // Step 3: Down Heapify
        int current = 0;
        int original;
        do {
            original = current;
            int smallest = original;
            int lChild = current * 2 + 1;
            int rChild = current * 2 + 2;

            // Find the smallest
            if(lChild < n && arr[lChild].weight < arr[smallest].weight)
                smallest = lChild;
            if(rChild < n && arr[rChild].weight < arr[smallest].weight)
                smallest = rChild;

            if(smallest != current) {
                std::swap(arr[current], arr[smallest]);
                current = smallest;
            }
        } while(current != original);
    }

    return temp;
}

// Used to check if graph is disconnected
bool areAllNodesVisited(bool arr[], int arrSize) {
    for(int i = 0; i < arrSize; i++) {
        if(arr[i] == false)
            return false;
    }
    return true;
}

// Prim's algorithm to find the MST
int Graph::primMST(std::vector<int>& mstStart, std::vector<int>& mstEnd) {
    int cost;

    // Steps:

    // 1. Initialize visited array and minWeight array
    bool visitedArray[numNodes];
    for(int i = 0; i < numNodes; i++) {
        visitedArray[i] = false;
    }
    std::vector<Edge> minWeight;

    // 2. Start from node 1
    int vertex = 1;
    visitedArray[vertex - 1] = true;
    int matrixSize = adjMatrix[0].size();
    for(int i = 0; i < matrixSize; i++) {
        if(adjMatrix[vertex - 1][i] != INF && adjMatrix[vertex - 1][i] != 0) {
            Edge tempEdge;
            tempEdge.node1 = vertex;
            tempEdge.node2 = i + 1;
            tempEdge.weight = adjMatrix[vertex - 1][i];
            minWeight.push_back(tempEdge);
        }
    }

    minWeight = heapSort(minWeight);

    while(!minWeight.empty()) {
        // 3. Use a loop to find the minimum weight edge at each step

        Edge* edgeToTakePtr = nullptr; // To check later if there is a valid edge to take (I am using a ptr because edgeToTake can't be NULL)
        Edge edgeToTake;
        int heapSize = minWeight.size();
        for(int i = 0; i < heapSize; i++) {
            Edge currentEdge;

            // Take from heap
            if(heapSize > 0) {
                currentEdge = minWeight[0];
                minWeight.erase(minWeight.begin());
                heapSize--;
            } else {
                break;
            }

            // Check if edge's distination node is already visited
            if(visitedArray[currentEdge.node2 - 1] == false) {
                edgeToTake = currentEdge;
                edgeToTakePtr = &edgeToTake;
                break;
            }
        }

        // Check if no MST exists
        if(edgeToTakePtr == nullptr && !areAllNodesVisited(visitedArray, numNodes)) {
            std::cerr << "Error: no MST exists for this graph" << std::endl;
            mstStart.clear();
            mstEnd.clear();
            return -1;
        }

        // Stop prims algorithm if minWeight is empty and all edges' destination nodes were visited
        if(edgeToTakePtr == nullptr) {
            break;
        }

        // 4. Update MST edges (mstStart and mstEnd vectors)
        mstStart.push_back(edgeToTake.node1);
        mstEnd.push_back(edgeToTake.node2);
        cost += edgeToTake.weight;
        vertex = edgeToTake.node2;
        visitedArray[vertex - 1] = true;

        // Add vertex's edges to heap
        int adjMatrixSize = adjMatrix[0].size();
        for(int i = 0; i < adjMatrixSize; i++) {
            if(adjMatrix[vertex - 1][i] != INF && adjMatrix[vertex - 1][i] != 0) {
                Edge tempEdge;
                tempEdge.node1 = vertex;
                tempEdge.node2 = i + 1;
                tempEdge.weight = adjMatrix[vertex - 1][i];
                minWeight.push_back(tempEdge);
            }
        }
        minWeight = heapSort(minWeight);
    }

    // 5. Return the total cost of the MST
    return cost; 
}
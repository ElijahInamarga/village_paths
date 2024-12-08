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
        adjMatrix[vertex2 - 1][vertex1 - 1] = weight; // The graph is undirected
    }

    // DELETE LATER!!!
    // Print adjacency matrix 
    // for(int i = 0; i < numNodes; i++) {
    //     for(int j = 0; j < numNodes; j++) {
    //         std::cout << adjMatrix[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }
    
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
    // Build the heap using upheap
    for(int i = 0; i < arr.size(); i++) {
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

// Prim's algorithm to find the MST
int Graph::primMST(std::vector<int>& mstStart, std::vector<int>& mstEnd) {
    // Placeholder for visited nodes and minimum weight initialization
    // std::cout << "TODO: Implement Prim's algorithm here.\n";
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
    for(int i = 0; i < adjMatrix[0].size(); i++) {
        if(adjMatrix[vertex - 1][i] != 0) {
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
        Edge* edgeToTakePtr = nullptr;
        Edge edgeToTake;
        int size = minWeight.size();
        for(int i = 0; i < size; i++) {
            Edge currentEdge;
            if(size > 0) {
                currentEdge = minWeight[0];
                minWeight.erase(minWeight.begin());
                size--;
            } else {
                break;
            }

            if(visitedArray[currentEdge.node2 - 1] == false) {
                edgeToTake = currentEdge;
                edgeToTakePtr = &edgeToTake;
                break;
            }
        }

        // If minWeight is empty and all edges' destination nodes were visited
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
        for(int i = 0; i < adjMatrix[0].size(); i++) {
            if(adjMatrix[vertex - 1][i] != 0) {
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

    return cost; // TODO: Return the actual total cost of the MST
}
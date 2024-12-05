#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <map>
#include <limits>
#include <string>

using namespace std;

const int INF = numeric_limits<int>::max();

class Graph {
private:
    map<int, map<int, int>> adjList; // adjacency list: node -> {neighbor, weight}
    map<int, int> traffic;          // traffic data: node -> traffic level

public:
    // Add edge to the graph
    void addEdge(int u, int v, int weight);

    // Set traffic level for a node
    void setTraffic(int node, int trafficLevel);

    // Get the shortest path using Dijkstra's Algorithm
    vector<int> shortestPath(int start, int end);

    // Find the busiest node based on traffic data
    int findBusiestNode();

    // Find alternate safe routes avoiding a specific node
    vector<int> safeRoute(int start, int end, int blockedNode);

    // Find the path with the lowest total weight (different from shortest path in distance)
    vector<int> lowestWeightPath(int start, int end);

    // Find all reachable nodes from a given start node
    vector<int> reachableNodes(int start);

};

#endif // GRAPH_H


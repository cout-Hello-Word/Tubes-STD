#include "graph.h"

int main() {
    Graph graph;

    // Add edges
    graph.addEdge(1, 2, 4);
    graph.addEdge(1, 3, 2);
    graph.addEdge(2, 3, 1);
    graph.addEdge(2, 4, 5);
    graph.addEdge(3, 4, 8);
    graph.addEdge(4, 5, 6);

    // Set traffic levels
    graph.setTraffic(1, 10);
    graph.setTraffic(2, 20);
    graph.setTraffic(3, 15);
    graph.setTraffic(4, 30);
    graph.setTraffic(5, 5);

    // Shortest path
    cout << "Shortest Path from 1 to 5: ";
    vector<int> path = graph.shortestPath(1, 5);
    for (int node : path) cout << node << " ";
    cout << endl;

    // Find busiest node
    int busiestNode = graph.findBusiestNode();
    cout << "Busiest Node: " << busiestNode << endl;

    // Safe route avoiding a specific node
    cout << "Safe Route from 1 to 5 avoiding node 4: ";
    vector<int> safePath = graph.safeRoute(1, 5, 4);
    for (int node : safePath) cout << node << " ";
    cout << endl;

    // Path with the lowest total weight
    cout << "Path with Lowest Weight from 1 to 5: ";
    vector<int> lowWeightPath = graph.lowestWeightPath(1, 5);
    for (int node : lowWeightPath) cout << node << " ";
    cout << endl;

    // All reachable nodes from a start node
    cout << "Nodes Reachable from 1: ";
    vector<int> reachable = graph.reachableNodes(1);
    for (int node : reachable) cout << node << " ";
    cout << endl;

    return 0;
}

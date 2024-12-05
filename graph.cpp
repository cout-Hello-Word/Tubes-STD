#include "graph.h"
#include <queue>
#include <set>
#include <algorithm> // for reverse

// Add edge to the graph
void Graph::addEdge(int u, int v, int weight) {
    adjList[u][v] = weight;
    adjList[v][u] = weight; // Assuming undirected graph
}

// Set traffic level for a node
void Graph::setTraffic(int node, int trafficLevel) {
    traffic[node] = trafficLevel;
}

// Get the shortest path using Dijkstra's Algorithm
vector<int> Graph::shortestPath(int start, int end) {
    map<int, int> dist;
    map<int, int> parent;
    set<int> visited;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    // Initialize distances
    for (auto& node : adjList) dist[node.first] = INF;
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int current = pq.top().second;
        pq.pop();

        if (visited.count(current)) continue;
        visited.insert(current);

        for (auto& neighbor : adjList[current]) {
            int next = neighbor.first;
            int weight = neighbor.second;

            if (dist[current] + weight < dist[next]) {
                dist[next] = dist[current] + weight;
                parent[next] = current;
                pq.push({dist[next], next});
            }
        }
    }

    // Backtrack to find the path
    vector<int> path;
    if (dist[end] == INF) return path; // No path found

    for (int at = end; at != start; at = parent[at]) path.push_back(at);
    path.push_back(start);
    reverse(path.begin(), path.end());
    return path;
}

// Find the busiest node based on traffic data
int Graph::findBusiestNode() {
    int busiestNode = -1;
    int maxTraffic = -1;

    for (auto& t : traffic) {
        if (t.second > maxTraffic) {
            maxTraffic = t.second;
            busiestNode = t.first;
        }
    }

    return busiestNode;
}

// Find alternate safe routes avoiding a specific node
vector<int> Graph::safeRoute(int start, int end, int blockedNode) {
    map<int, int> dist;
    map<int, int> parent;
    set<int> visited;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    // Initialize distances
    for (auto& node : adjList) dist[node.first] = INF;
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int current = pq.top().second;
        pq.pop();

        if (current == blockedNode || visited.count(current)) continue;
        visited.insert(current);

        for (auto& neighbor : adjList[current]) {
            int next = neighbor.first;
            int weight = neighbor.second;

            if (dist[current] + weight < dist[next]) {
                dist[next] = dist[current] + weight;
                parent[next] = current;
                pq.push({dist[next], next});
            }
        }
    }

    // Backtrack to find the path
    vector<int> path;
    if (dist[end] == INF) return path; // No path found

    for (int at = end; at != start; at = parent[at]) path.push_back(at);
    path.push_back(start);
    reverse(path.begin(), path.end());
    return path;
}

// Find the path with the lowest total weight
vector<int> Graph::lowestWeightPath(int start, int end) {
    map<int, int> dist;
    map<int, int> parent;
    set<int> visited;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    // Initialize distances
    for (auto& node : adjList) dist[node.first] = INF;
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int current = pq.top().second;
        pq.pop();

        if (visited.count(current)) continue;
        visited.insert(current);

        for (auto& neighbor : adjList[current]) {
            int next = neighbor.first;
            int weight = neighbor.second;

            if (dist[current] + weight < dist[next]) {
                dist[next] = dist[current] + weight;
                parent[next] = current;
                pq.push({dist[next], next});
            }
        }
    }

    // Backtrack to find the path
    vector<int> path;
    if (dist[end] == INF) return path; // No path found

    for (int at = end; at != start; at = parent[at]) path.push_back(at);
    path.push_back(start);
    reverse(path.begin(), path.end());
    return path;
}

// Find all reachable nodes from a given start node
vector<int> Graph::reachableNodes(int start) {
    vector<int> reachable;
    set<int> visited;
    queue<int> q;

    q.push(start);
    visited.insert(start);

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        reachable.push_back(current);

        for (auto& neighbor : adjList[current]) {
            int next = neighbor.first;
            if (!visited.count(next)) {
                q.push(next);
                visited.insert(next);
            }
        }
    }

    return reachable;
}

#include "Graph.h"
#include <queue>
#include <cassert>
#include "..\..\Visualizer\Scene.h"
const int Dijkstra::INF = 1e5;

Dijkstra::Dijkstra(int nodes, int start) : nodes(nodes), start(start), isRun(false) {
    adj.resize(nodes);
    dist.assign(nodes, INF);
    traverse.assign(nodes, -1);
}

void Dijkstra::addEdge(int from, int to, int weight) {
    adj[from].emplace_back(to, weight);
}

void Dijkstra::run() {  
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    dist[start] = 0;
    pq.emplace(0, start);
    while (!pq.empty()) {
        auto[distance, node] = pq.top();
        pq.pop();
        if (distance != dist[node]) continue;
        for (auto [next, weight] : adj[node]) {
            int newDist = dist[node] + weight;
            if (newDist < dist[next]) {
                dist[next] = newDist;
                traverse[next] = node;
                pq.emplace(newDist, next);
            }
        }
    }
    isRun = true;
}

int Dijkstra::getDistance(int node) {
    assert(isRun == true);
    return dist[node];
}

int Dijkstra::getTraverse(int node) {
    assert(isRun == true);
    return traverse[node];
}


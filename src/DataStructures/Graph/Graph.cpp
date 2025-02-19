#include <iostream>
#include <list>
#include <queue>
using namespace std;

#include "Graph.h"  

Graph::Graph(int V) {
    this->V = V;
    adjList = new list<isPair>[V];
}

void Graph::addEdge(int u, int v, int w) {
    adjList[u].push_back(make_pair(v, w));
    adjList[v].push_back(make_pair(u, w));
}

void Graph::shortestPath(int src) {
    priority_queue<isPair, vector<isPair>, greater<isPair>> pq;

    vector<int> dist(V, INF);

    pq.push(make_pair(0, src));
    dist[src] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (auto &neighbor : adjList[u]) {
            int v = neighbor.first;
            int w = neighbor.second;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    cout << "Vertex Distance from Source" << endl;
    for (int i = 0; i < V; i++) {
        cout << i << "\t\t" << dist[i] << endl;
    }
}
#include <iostream>
#include <list>
#include <queue>
#include <string>
using namespace std;

#include "Graph.h"  

// Adj List Graph
AdjListGraph::AdjListGraph(int V, bool isDirected) {
    this->V = V;
    this->isDirected = isDirected;
    adjList = new list<isPair>[V];
}

AdjListGraph::~AdjListGraph() {
    delete[] adjList;
}

void AdjListGraph::addEdge(int u, int v, int w) {
    adjList[u].push_back(make_pair(v, w));
    if (isDirected) {
        adjList[v].push_back(make_pair(u, w));
    }
}

void AdjListGraph::shortestPath(int src) {
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

    cout << "Vertex \t Distance from Source" << endl;
    for (int i = 0; i < V; ++i) {
        cout << i << " \t\t" << (dist[i] == INF ? "INF" : to_string(dist[i])) << endl;
    }
}

// Adj Matrix Graph
AdjMatrixGraph::AdjMatrixGraph(int V, bool isDirected) {
    this->V = V;
    this->isDirected = isDirected;
    this->adjMatrix = vector(V, (V, vector<int>(V, INF)));
}

void AdjMatrixGraph::addEdge(int u, int v, int w) {
    adjMatrix[u][v] = w;
    if (isDirected) {
        adjMatrix[v][u] = w;
    }
}

void AdjMatrixGraph::shortestPath(int src) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    
    vector<int> dist(V, INF);

    pq.push(make_pair(0, src));
    dist[src] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        int w = pq.top().first;
        pq.pop();

        if (w > dist[u]) continue;

        for (int v = 0; v < V; v++) {
            if (adjMatrix[u][v] != INF && dist[u] + adjMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + adjMatrix[u][v];
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    
    cout << "Vertex \t Distance from Source" << endl;
    for (int i = 0; i < V; i++) {
        cout << i << " \t\t" << (dist[i] == INF ? "INF" : to_string(dist[i])) << endl;
    }
}
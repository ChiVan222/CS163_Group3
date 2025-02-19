#pragma once
#include <iostream>
#include <list>
#include <queue>
using namespace std;

#define INF 0x3f3f3f3f
typedef pair<int, int> isPair;

class Graph {
    private:    
        int V;  
        list<isPair> *adjList;
    public:
        Graph(int V);

        void addEdge(int u, int v, int w);
        void shortestPath(int s); 
};
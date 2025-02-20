#pragma once
#include <iostream>
#include <list>
#include <queue>
using namespace std;

#define INF 0x3f3f3f3f
typedef pair<int, int> isPair;

class Graph {
    public:
        virtual void addEdge(int u, int v, int w) = 0;
        virtual void shortestPath(int src) = 0;
};

class AdjListGraph : public Graph {
    private:    
        int V;  
        bool isDirected;
        list<isPair> *adjList;
    public:
        AdjListGraph(int V, bool isDirected);
        ~AdjListGraph();
        void addEdge(int u, int v, int w) override;
        void shortestPath(int src) override;
};

class AdjMatrixGraph : public Graph {
    private:
        int V;
        bool isDirected;
        vector<vector<int>> adjMatrix;
    public:
        AdjMatrixGraph(int V, bool isDirected);
        void addEdge(int u, int v, int w) override;
        void shortestPath(int src) override;
};
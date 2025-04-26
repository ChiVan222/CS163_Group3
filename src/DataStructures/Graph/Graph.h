#pragma once
#include <vector>
using namespace std;

#include "../../Visualizer/GraphNode.h"


 class Dijkstra {
    private:
        bool isRun;
        int nodes;
        int start;
        vector<vector<pair<int, int>>> adj;
        vector<int> dist;
        vector<int> traverse;
    public:
        static const int INF;   
        
        Dijkstra(int nodes, int start);
        void addEdge(int from, int to, int weight);
        void run();

        int getDistance(int node);
        int getTraverse(int node);
 };
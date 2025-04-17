#pragma once
#include "Animation.h"
#include "GraphNode.h"
#include "Edge.h"
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>

class Ani_GraphInsert : public Animations {
public:
    Ani_GraphInsert();
    Ani_GraphInsert(float duration, int value, float radius, Vector2 position);
    void updateAnimations(float deltaTime) override;
    void updateTarget(GraphNode* node);

private:
    int value;
    float radius;
    Vector2 position, src_pos;
    GraphNode* node_insert;
    void play(GraphNode* node);
    void play() override;
};

class Ani_GraphSearch : public Animations {
public:
    Ani_GraphSearch();
    Ani_GraphSearch(float duration, int value);
    void updateAnimations(float deltaTime) override;
    void updateTarget(GraphNode* startNode);

private:
    int value;
    GraphNode* curNode;
    std::stack<GraphNode*> toVisit;
    std::unordered_set<GraphNode*> visited;
    void play() override;
};

class Ani_GraphRemove : public Animations {
public:
    Ani_GraphRemove();
    Ani_GraphRemove(float duration);
    void updateAnimations(float deltaTime) override;
    void updateTarget(GraphNode* removeNode);

private:
    GraphNode* targetNode;
    void play() override;
};

class Ani_Dijkstra : public Animations {
public:
    Ani_Dijkstra();
    Ani_Dijkstra(float duration, int nodes);
    ~Ani_Dijkstra();
    void updateAnimations(float deltaTime) override;
    void play() override;
    void updateTarget(GraphNode* start);
    void prerun(GraphNode* start);
private:
    GraphNode* cur;
    Edge* curEdge;
    std::unordered_set<GraphNode*> visited;
    std::unordered_map<GraphNode*, std::unordered_set<GraphNode*>> mp;
    std::unordered_map<int, int> dist;
    std::priority_queue<std::pair<int, GraphNode*>, std::vector<std::pair<int, GraphNode*>>, std::greater<>> pq;
    struct DijkstraSnapshot {
        GraphNode* cur;
        std::unordered_set<GraphNode*> visited;
        std::unordered_map<GraphNode*, std::unordered_set<GraphNode*>> mp;
        std::unordered_map<int, int> dist;
        Edge* curEdge;
    };
    std::vector<DijkstraSnapshot> history;
    int currentStep = -1;
    bool isPrerunDone = false;
};

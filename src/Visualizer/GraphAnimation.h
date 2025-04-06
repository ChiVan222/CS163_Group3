#pragma once
#include "Animation.h"
#include "GraphNode.h"
#include "Edge.h"
#include <unordered_set>
#include <stack>

class Ani_GraphInsert : public Animations {
public:
    Ani_GraphInsert();
    Ani_GraphInsert(float duration, int value, float radius, Vector2 position);
    void updateAnimations(float deltaTime) override;
    void updateTarget(GraphNode*& node);

private:
    int value;
    float radius;
    Vector2 position, src_pos;
    GraphNode* node_insert;
    void play(GraphNode*& node);
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
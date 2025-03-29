#pragma once

#include <memory>

#include "PolyNode.h"
#include "..\DataStructures\Graph\Graph.h"

class GraphNode : public PolyNode
{
public:
    int val;
    GraphNode(Vector2 position, float radius, int value);
    bool Draw() override;
    void drawNodes() const;
    void drawEdges() const;
    void setPosition(Vector2 position);
    Vector2 getPosition() const;

    // Vector2 nVelocity;
    // void setVelocity(Vector2 nVelocity);
    // void updateCurrent(float dt);
    // Vector2 getRepulsion(const GraphNode& node) const;
    // bool isAdjacent(const GraphNode& node) const;
    // Vector2 getTotalAttraction() const;
    // Vector2 getAttraction(const GraphNode& node) const;
    // const std::vector<GraphNode*>& getAdj() const;

// public:
//     typedef unique_ptr<GraphNode> Ptr;
//     static const float repulse;
//     static const float attract;
//     static const float lenghtLimit;
//     static const float left, right, top, bottom;
};
#pragma once

#include <memory>

#include "PolyNode.h"
#include "..\DataStructures\Graph\Graph.h"

class GraphNode : public PolyNode {
public:
    GraphNode(Vector2 position, float radius, int value);
    bool Draw() override;
    void setPosition(Vector2 position);
    Vector2 getPosition() const;
    void makeAdjacent(GraphNode* node);
    const std::vector<GraphNode*>& getAdj() const;
    void repulseNearbyNodes(float minDistance);
    int val;

    static const float REPULSE_STRENGTH;
    static const float LEFT, RIGHT, TOP, BOTTOM;

private:
    Vector2 velocity;    
    std::vector<GraphNode*> adj;
    void drawNodes() const;
    void drawEdges() const;
};
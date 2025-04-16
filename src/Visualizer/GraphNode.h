#pragma once

#include <memory>
#include <sstream>

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
    void highlight(Color color);

    static const float REPULSE_STRENGTH;
    static const float LEFT, RIGHT, TOP, BOTTOM;

    void onClick();

private:
    Vector2 velocity;    
    std::vector<GraphNode*> adj;
    void drawNodes() const;
    void drawEdges() const;
    bool updateVal;
    std::string input;
    float lastDeletedTime = 0.0f;
    const float waitTime = 0.1f;
    const int maxInputLength = 10;
};
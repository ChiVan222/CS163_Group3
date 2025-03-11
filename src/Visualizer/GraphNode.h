#pragma once

#include <memory>

#include "PolyNode.h"
#include "..\DataStructures\Graph\Graph.h"

class GraphNode 
{
private:
    vector<GraphNode*> nAdj;
    Vector2 nVelocity;
    Vector2 nPosition;
public:
    typedef unique_ptr<GraphNode> Ptr;
    static const float repulse;
    static const float attract;
    static const float lenghtLimit;
    static const float left, right, top, bottom;
public:
    GraphNode();
    void setVelocity(Vector2 nVelocity);
    void makeAdjacent(GraphNode* node);
 
    Vector2 getRepulsion(const GraphNode& node) const;
    bool isAdjacent(const GraphNode& node) const;
    Vector2 getTotalAttraction() const;
    Vector2 getAttraction(const GraphNode& node) const;
    const std::vector<GraphNode*>& getAdj() const;

    void draw();
    void updateCurrent(float dt);
};
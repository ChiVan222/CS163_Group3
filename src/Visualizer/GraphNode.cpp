#include <cmath>
#include <algorithm>
#include "GraphNode.h"
#include "Edge.h"
#include "Scene.h"
// const float GraphNode::repulse = 5000000.f;
// const float GraphNode::attract = 2000.f;
// const float GraphNode::lenghtLimit = 175.f;
// const float GraphNode::left = -520.f;
// const float GraphNode::right = 520.f;
// const float GraphNode::top = 0.f;
// const float GraphNode::bottom = 600.f;

GraphNode::GraphNode() {
    // this->nVelocity = {0, 0};
    this->nPosition = {0, 0};
}

GraphNode::GraphNode(Vector2 position, int value) {
    this->val = value;
    setPosition(position);
}

void GraphNode::addEdge(GraphNode* to, int weight) {
    edges.push_back({to, weight});
}

void GraphNode::drawNodes() const {
    DrawCircleV(nPosition, 20, WHITE);
    DrawText(TextFormat("%d", val), nPosition.x - 10, nPosition.y - 10, 40, BLUE);
}

void GraphNode::drawEdges() const {
    for (const auto& edge : edges) {
        DrawLineV(nPosition, edge.first->nPosition, WHITE);
        Vector2 midPoint = {(nPosition.x + edge.first->nPosition.x)/2, (nPosition.y + edge.first->nPosition.y)/2};
        DrawText(TextFormat("%d", edge.second), midPoint.x, midPoint.y, 20, BLUE);
    }
}

void GraphNode::setPosition(Vector2 position){
    nPosition = position;
}

Vector2 GraphNode::getPosition() const {
    return nPosition;
}


// void GraphNode::setVelocity(Vector2 nVelocity) {
//     this->nVelocity = nVelocity;
// }

// Vector2 GraphNode::getRepulsion(const GraphNode& node) const {
//     Vector2 delta = {nPosition.x - node.nPosition.x, nPosition.y - node.nPosition.y};
//     float eDist = sqrt(delta.x * delta.x + delta.y * delta.y);
//     float eDistSquare = eDist * eDist;
//     return {(delta.x/eDist)/eDistSquare*repulse, (delta.y/eDist)/eDistSquare*repulse}; 
// }

// bool GraphNode::isAdjacent(const GraphNode& node) const {
//     for (auto& cur : nAdj) {
//         if (cur == &node) return true;
//     }
//     return false;
// }

// Vector2 GraphNode::getTotalAttraction() const {
//     Vector2 nAttract = {0, 0};
//     for(auto& cur : nAdj) {
//         Vector2 attraction = getAttraction(*cur);
//         nAttract.x += attraction.x;
//         nAttract.y += attraction.y;
//     }
//     return nAttract;
// }

// Vector2 GraphNode::getAttraction(const GraphNode& node) const {
//     Vector2 delta = {nPosition.x - node.nPosition.x, nPosition.y - node.nPosition.y};
//     float eDist = sqrt(delta.x * delta.x + delta.y * delta.y);
//     float ratio = log(eDist/lenghtLimit);
//     Vector2 repulsion = getRepulsion(node);
//     return {(delta.x/eDist)/ratio*attract - repulsion.x, (delta.y/eDist)/ratio*attract - repulsion.y};   
// }

// const std::vector<GraphNode*>& GraphNode::getAdj() const {
//     return nAdj;
// }

// void GraphNode::updateCurrent(float dt) {
//     nPosition.x += nVelocity.x * dt;
//     nPosition.y += nVelocity.y * dt;

//     nPosition.x = min(nPosition.x, right);
//     nPosition.x = max(nPosition.x, left);
//     nPosition.y = min(nPosition.y, bottom);
//     nPosition.y = max(nPosition.y, top);

//     nPosition.x = round(nPosition.x);
//     nPosition.y = round(nPosition.y);
// }
#include <cmath>
#include <algorithm>
#include "GraphNode.h"
#include "Edge.h"
#include "Scene.h"

#include <iostream>
// const float GraphNode::repulse = 5000000.f;
// const float GraphNode::attract = 2000.f;
// const float GraphNode::lenghtLimit = 175.f;
// const float GraphNode::left = -520.f;
// const float GraphNode::right = 520.f;
// const float GraphNode::top = 0.f;
// const float GraphNode::bottom = 600.f;

// need to be modified the construct of polynode
GraphNode::GraphNode(Vector2 position, float radius, int value) : PolyNode(position, radius), val(value){}

bool GraphNode::Draw() {
    drawNodes();
    drawEdges();
    return true;
}

void GraphNode::drawNodes() const {
    DrawCircleV(position, 20, WHITE);
    DrawText(TextFormat("%d", val), position.x - 10, position.y - 10, 20, BLUE);
}

void GraphNode::drawEdges() const {
    for (auto& edge : Graph_Scene::Edges) {
        edge->Draw();
    }
}

void GraphNode::setPosition(Vector2 position){
    this->position = position;
}

Vector2 GraphNode::getPosition() const {
    return position;
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
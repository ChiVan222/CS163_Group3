#include <cmath>
#include <algorithm>
#include "GraphNode.h"
#include "Edge.h"
#include "Scene.h"

#include <iostream>
const float GraphNode::LEFT = 500.0f;
const float GraphNode::RIGHT = 1600.0f;
const float GraphNode::TOP = 100.0f;
const float GraphNode::BOTTOM = 900.0f;
const float GraphNode::REPULSE_STRENGTH = 3.0f;

GraphNode::GraphNode(Vector2 position, float radius, int value) : PolyNode(position, radius), val(value), velocity({0,0})   {}

bool GraphNode::Draw() {
    drawNodes();
    drawEdges();
    return true;
}

void GraphNode::drawNodes() const {
    DrawCircleV(position, radius, WHITE);
    DrawText(TextFormat("%d", val), position.x - 10, position.y - 10, 20, BLUE);
}

void GraphNode::drawEdges() const {
    for(auto* edge : Graph_Scene::Edges) {
        edge->Draw(WHITE, 1);
    }
}

void GraphNode::setPosition(Vector2 position){
    this->position = position;
}

Vector2 GraphNode::getPosition() const {
    return position;
}

void GraphNode::makeAdjacent(GraphNode* node) {
    if (std::find(adj.begin(), adj.end(), node) == adj.end()) {
        adj.push_back(node);
    }
}

const std::vector<GraphNode*>& GraphNode::getAdj() const {
    return adj;
}

void GraphNode::repulseNearbyNodes(float minDistance) {
    for (auto* otherNode : Graph_Scene::graphNodes) {
        if (otherNode == this) continue;
        Vector2 delta = {position.x - otherNode->position.x, position.y - otherNode->position.y};
        float dist = sqrt(delta.x * delta.x + delta.y * delta.y);
        if (dist < minDistance && dist > 0.1f) {
            float force = REPULSE_STRENGTH * (minDistance - dist) / dist;
            Vector2 repulsion = {delta.x * force, delta.y * force};
            Vector2 newPos = otherNode->getPosition();
            newPos.x += repulsion.x;
            newPos.y += repulsion.y;    

            newPos.x = std::max(LEFT, std::min(RIGHT, newPos.x));
            newPos.y = std::max(TOP, std::min(BOTTOM, newPos.y));

            otherNode->setPosition(newPos);
        }
    }
}

void GraphNode::highlight(Color color) {
    for (float r = radius; r <= radius + 5.0f; r += 0.1f) {
        DrawCircleLinesV(position, r, color);
    }
}
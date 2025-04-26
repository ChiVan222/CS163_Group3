#include <iostream>
#include <cmath>
#include <algorithm>
#include "GraphNode.h"
#include "Edge.h"
#include "Scene.h"
#include "UI.h"

const float GraphNode::LEFT = 500.0f;
const float GraphNode::RIGHT = 1600.0f;
const float GraphNode::TOP = 100.0f;
const float GraphNode::BOTTOM = 900.0f;
const float GraphNode::REPULSE_STRENGTH = 3.0f;

GraphNode::GraphNode(Vector2 position, float radius, int value) : PolyNode(position, radius), velocity({0,0}), updateVal(false)   {
    val = value;
    input = std::to_string(val);
}

bool GraphNode::Draw() {
    drawEdges();
    drawNodes();
    return true;
}

void GraphNode::drawNodes() const { 
    DrawCircleV(position, radius, colorNode);
    int textWidth = MeasureText(input.c_str(), radius);
    int textHeight = radius;
    Vector2 textPos = {position.x - textWidth/2, position.y - textHeight/2};
    float luminance = 0.299f * colorNode.r + 0.587f * colorNode.g + 0.114f * colorNode.b;
    Color textColor = (luminance < 128.0f) ? WHITE : BLACK;
    DrawText(input.c_str(), textPos.x, textPos.y, radius, textColor);
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
    for (float r = radius; r <= radius + 7.0f; r += 0.05f) {
        DrawCircleLinesV(position, r, GetHighlightColor2(color, 30.0));
    }
}

bool isSafeSTOI(const std::string& str, int& newVal) {
    std::istringstream iss(str);
    int val;
    if (iss >> val && iss.eof()) {
        newVal = val;
        return true;
    }
    return false;
}

bool isValidVal(int newVal) {
    for (auto* node : Graph_Scene::graphNodes) {
        if (node->val == newVal) return false;
    }
    return true;
}

void GraphNode::onClick() {
    if (Graph_Scene::ani == None) {
        Vector2 mousePos = UI::mousePos;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointCircle(mousePos, position, radius)) {
            std::cout << "Updating new value" << val << "\n";
            updateVal = true;
        }
        else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            updateVal = false;
            input = std::to_string(val);
        }

        if (updateVal) {
            highlight(colorNode);
            int key = GetCharPressed();
            while (key > 0) {
                if (key >= 32 && key <= 125 && input.size() < maxInputLength) {
                    input += char(key);
                }
                std::cout << "Added " << char(key) << "\n";
                key = GetCharPressed();
            }

            if (GetTime() - lastDeletedTime >= waitTime) {
                if(IsKeyDown(KEY_BACKSPACE) && !input.empty()) {
                    input.pop_back();
                    lastDeletedTime = GetTime();
                }
            }

            if (IsKeyDown(KEY_ENTER)) {
                int newVal;
                if (isSafeSTOI(input, newVal) && isValidVal(newVal)) {
                    val = newVal;
                    std::cout << "Node->val is updated to " << newVal << "\n";
                }
                else {
                    std::cout << "Invalid or duplicate value\n";
                }
                updateVal = false;
            }
        }
    }
}
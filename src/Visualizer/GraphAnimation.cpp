#include "GraphAnimation.h"
#include "Scene.h"
#include <iostream>
#include <math.h>

// Inserting animations
Ani_GraphInsert::Ani_GraphInsert() : Animations(0) {}

Ani_GraphInsert::Ani_GraphInsert(float duration, int value, float radius, Vector2 position) : 
Animations(duration), value(value), radius(radius), position(position)
{
    src_pos = Vector2({100, 100});
    node_insert = nullptr;
    isDone = true;
}

void Ani_GraphInsert::updateAnimations(float deltaTime) {
    if (isDone || !node_insert) return;
    elapsed_time += deltaTime;

    node_insert->setPosition(Vector2{
        std::min(position.x, (elapsed_time/duration)*position.x),
        std::min(position.y, (elapsed_time/duration)*position.y)
    });

    if (elapsed_time >= duration) {
        isDone = true;
        elapsed_time = 0;
        Graph_Scene::ani = None;
    }
}

void Ani_GraphInsert::play(GraphNode*& node) {
    node_insert = node;
    node_insert->setPosition(src_pos);
    Graph_Scene::graphNodes.push_back(node_insert);
    isDone = false;
}

void Ani_GraphInsert::play() {}

void Ani_GraphInsert::updateTarget(GraphNode*& node) {
    if (isDone && Graph_Scene::ani == None) {
        std::cout << "Update target " << value << "\n";
        Graph_Scene::ani = Inserting;
        this->value = node->val;
        this->radius = node->getRadius();
        this->position = node->getPosition();
        play(node);
    }
    else {
        cout << "ani != None or !isDone\n";
    }
}

// Searching animations
Ani_GraphSearch::Ani_GraphSearch() : Animations(2.0f), value(0), curNode(nullptr) {};

Ani_GraphSearch::Ani_GraphSearch(float duration, int value) : Animations(duration), value(value), curNode(nullptr) {
    isDone = true;
}; 

void Ani_GraphSearch::updateAnimations(float deltaTime) {
    if (isDone || toVisit.empty() && !curNode) return;
    elapsed_time += deltaTime;

    if (!curNode || elapsed_time >= duration && curNode->val != value) {
        if (curNode) {
            const std::vector<GraphNode*> adj = curNode->getAdj();
            for (auto* neighbor : adj) {
                if (visited.find(neighbor) == visited.end()) {
                    toVisit.push(neighbor);
                    visited.insert(neighbor);
                }
            }
        }
        if (!toVisit.empty()) {
            curNode = toVisit.top();
            toVisit.pop();
            elapsed_time = 0;
        }
        else {
            curNode = nullptr;
            isDone = true;
            Graph_Scene::ani = None;
            std::cout << "Not Found " << value << "\n";
            return;
        }
    }

    if (curNode->val == value) {
        DrawCircleV(curNode->getPosition(), curNode->getRadius() + 5, GREEN);
        if (elapsed_time >= duration) {
            isDone = true;
            Graph_Scene::ani = None;
            std::cout << "Found " << value << "\n";
            return;
        }
    }
    else {
        DrawCircleV(curNode->getPosition(), curNode->getRadius() + 5, RED);
    }
}

void Ani_GraphSearch::play() {
    std::cout << "Play DFS\n";
    isDone = false;
}

void Ani_GraphSearch::updateTarget(GraphNode* startNode) {
    if (isDone && Graph_Scene::ani == None) {
        std::cout << "Update Target Searching\n";
        Graph_Scene::ani = Searching;
        curNode = nullptr;
        visited.clear();
        for (auto* node : Graph_Scene::graphNodes) {
            if (node->getAdj().empty() && node != startNode) {
                toVisit.push(node);
                visited.insert(node);
            }
        }
        toVisit.push(startNode);
        visited.insert(startNode);
        play();
    }
}

// Removing Animations
Ani_GraphRemove::Ani_GraphRemove() : Animations(0), targetNode(nullptr) {};

Ani_GraphRemove::Ani_GraphRemove(float duration) : Animations(duration), targetNode(nullptr) {
    isDone = true;
}

void Ani_GraphRemove::updateAnimations(float deltaTime) {
    if (isDone || !targetNode) return;
    elapsed_time += deltaTime;

    for (float r = targetNode->getRadius(); r <= targetNode->getRadius() + 5.0f; r += 1.0f) {
        DrawCircleLinesV(targetNode->getPosition(), r, RED);
    }
    for (auto* edge : Graph_Scene::Edges) {
        if (edge->getFrom() == targetNode || edge->getTo() == targetNode) {
            float theta = atan2(edge->getTo()->getPosition().y - edge->getFrom()->getPosition().y, 
                                edge->getTo()->getPosition().x - edge->getFrom()->getPosition().x);

            Vector2 cpos = Vector2({targetNode->getRadius() * cos(theta) + edge->getFrom()->getPosition().x,
                                    targetNode->getRadius() * sin(theta) + edge->getFrom()->getPosition().y});

            Vector2 dpos = Vector2({edge->getTo()->getPosition().x - targetNode->getRadius() * cos(theta),
                                    edge->getTo()->getPosition().y - targetNode->getRadius() * sin(theta)});
            DrawLineEx(cpos, dpos, 2, RED);
        }
    }

    if (elapsed_time >= duration) {
        auto& nodes = Graph_Scene::graphNodes;
        auto& edges = Graph_Scene::Edges;
        for (auto* node : nodes) {
            auto& adj = const_cast<std::vector<GraphNode*>&>(node->getAdj());  
            adj.erase(std::remove(adj.begin(), adj.end(), targetNode), adj.end());
        }
        nodes.erase(std::remove(nodes.begin(), nodes.end(), targetNode), nodes.end());
        edges.erase(std::remove_if(edges.begin(), edges.end(), [this](Edge* e) {return e->getFrom() == targetNode || e->getTo() == targetNode;}), edges.end());
        int value = targetNode->val;
        delete targetNode;
        targetNode = nullptr;
        isDone = true;
        Graph_Scene::ani = None;
        elapsed_time = 0;
        std::cout << "Removed " << value << "\n";
    }
}

void Ani_GraphRemove::play() {
    std::cout << "Play remove\n";
    isDone = false;
}

void Ani_GraphRemove::updateTarget(GraphNode* removeNode) {
    if (isDone && Graph_Scene::ani == None) {
        std::cout << "Update Target Removing\n";
        Graph_Scene::ani = Removing;
        targetNode = removeNode;
        play();
    }
}
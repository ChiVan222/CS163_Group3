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

void Ani_GraphInsert::play(GraphNode* node) {
    node_insert = node;
    node_insert->setPosition(src_pos);
    Graph_Scene::graphNodes.push_back(node_insert);
    isDone = false;
}

void Ani_GraphInsert::play() {}

void Ani_GraphInsert::updateTarget(GraphNode* node) {
    if (isDone && Graph_Scene::ani == None) {
        std::cout << "Update target " << value << "\n";
        Graph_Scene::ani = Inserting;
        this->value = node->val;
        this->radius = node->getRadius();
        this->position = node->getPosition();
        play(node);
    }
    else {
        std::cout << "ani != None or !isDone\n";
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
            visited.insert(curNode);
            auto& adj = curNode->getAdj();
            for (auto* neighbor : adj) {
                if (visited.find(neighbor) == visited.end()) {
                    toVisit.push(neighbor);
                }
            }
        }
        if (!toVisit.empty() && visited.size() != Graph_Scene::graphNodes.size()) {
            curNode = toVisit.top();
            toVisit.pop();
            elapsed_time = 0;
        }
        else if (visited.size() != Graph_Scene::graphNodes.size()) {
            for (auto* left : Graph_Scene::graphNodes) {
                if (visited.find(left) == visited.end()) {
                    toVisit.push(left);
                    break;
                }
            }
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
        curNode->highlight(GREEN);
        if (elapsed_time >= duration) {
            isDone = true;
            Graph_Scene::ani = None;
            std::cout << "Found " << value << "\n";
            return;
        }
    }
    else {
        curNode->highlight(RED);
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
        while(!toVisit.empty()) toVisit.pop();
        toVisit.push(startNode);
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

    targetNode->highlight(RED);
    for (auto* edge : Graph_Scene::Edges) {
        if (edge->getFrom() == targetNode || edge->getTo() == targetNode) {
            edge->Draw(RED, 1);
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

// Dijkstra Algorithm Animations
const int INF = INT_MAX;
Ani_Dijkstra::Ani_Dijkstra() : Animations(1.0), cur(nullptr), curEdge(nullptr) {
    std::cout << "Construct Ani_Dijkstra1\n";
}
Ani_Dijkstra::Ani_Dijkstra(float duration, int nodes) : Animations(duration), cur(nullptr), curEdge(nullptr) {
    isDone = true;
    dist.resize(nodes, INF);
    std::cout << "Construct Ani_Dijkstra\n";
}
Ani_Dijkstra::~Ani_Dijkstra() { 
    cur = nullptr;
    delete cur;
    curEdge = nullptr;
    delete curEdge;
}

void Ani_Dijkstra::updateAnimations(float deltaTime) {
    if (isDone || !cur) return;
    elapsed_time += deltaTime;

    for (auto* node : Graph_Scene::graphNodes) {
        if (node) {
            std::string text = (dist[node->val] == INF) ? "INF" : std::to_string(dist[node->val]);
            DrawText(text.c_str(), node->getPosition().x - 10, node->getPosition().y - 50, 15, YELLOW);

            if (visited.find(node) != visited.end() && node != cur) {
                node->highlight(GREEN); 
            } 
            else if (cur && node == cur && elapsed_time < duration) {
                node->highlight(ORANGE); 
            }
        }
    }
    if (curEdge && elapsed_time < duration) {
        curEdge->Draw(ORANGE, 1);
        static_cast<GraphNode*>(curEdge->getTo())->highlight(ORANGE);
    }
    if (elapsed_time >= duration && cur) {
        auto neighbors = cur->getAdj();
        bool processedAllNeighbors = true;

        for (auto* v : neighbors) {
            if (mp[cur].find(v) != mp[cur].end()) continue;
            curEdge = nullptr;
            for (auto* edge : Graph_Scene::Edges) {
                if ((edge->getFrom() == cur && edge->getTo() == v) ||
                    (edge->getFrom() == v && edge->getTo() == cur)) {
                    curEdge = edge;
                    break;
                }
            }
            if (!curEdge) std::cout << "Warning no edges from " << cur->val << "\n";
            mp[cur].insert(v);
            mp[v].insert(cur);

            if (visited.find(v) == visited.end()) {
                int weight = curEdge->weight;
                if (dist[v->val] > dist[cur->val] + weight) {
                    dist[v->val] = dist[cur->val] + weight;
                    pq.push({dist[v->val], v});
                    std::cout << "Updated dist[" << v->val << "] = " << dist[v->val] << "\n";
                }
            }

            elapsed_time = 0;
            processedAllNeighbors = false;
            break;
        }

        if (processedAllNeighbors) {
            visited.insert(cur);
            mp.erase(cur);
            cur = nullptr;
            curEdge = nullptr;
            while (!pq.empty()) {
                auto [d, v] = pq.top();
                pq.pop();
                if (visited.find(v) == visited.end()) {
                    cur = v;
                    std::cout << "Processing node with value: " << cur->val << " and dist: " << d << "\n";
                    break;
                }
            }
        }

        if (!cur) {
            isDone = true;
            Graph_Scene::ani = None;
            std::cout << "Dijkstra is completed!\n";
        }

    }
}

void Ani_Dijkstra::play() {
    std::cout << "Play Dijkstra for undirected graph\n";
    isDone = false;
}

void Ani_Dijkstra::updateTarget(GraphNode* start) {
    if (isDone && Graph_Scene::ani == None) {
        std::cout << "Update Target Dijkstra\n";
        Graph_Scene::ani = DijkstraRunning;
        cur = start;
        curEdge = nullptr;
        dist.resize(Graph_Scene::graphNodes.size(), INF);
        dist[start->val] = 0;
        visited.clear();
        mp.clear();
        while (!pq.empty()) pq.pop();
        pq.push({0, start});
        visited.insert(start);
        std::cout << "Next to play\n";
        play();
    }
}
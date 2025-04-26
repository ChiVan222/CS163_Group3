#include "GraphAnimation.h"
#include "Scene.h"
#include "UI.h"
#include <iostream>
#include <math.h>
#include <iterator>

// Inserting animations
Ani_GraphInsert::Ani_GraphInsert() : Animations(0) {}

Ani_GraphInsert::Ani_GraphInsert(float duration, int value, float radius, Vector2 position) : 
Animations(duration), value(value), radius(radius), position(position)
{
    src_pos = GetScreenToWorld2D({100, 100}, UI::camera);
    node_insert = nullptr;
    isDone = true;
}

void Ani_GraphInsert::updateAnimations(float deltaTime) {
    if (isDone || !node_insert || Graph_Scene::ani == None) return;
    elapsed_time += deltaTime;

    
    node_insert->setPosition(Vector2{
        (position.x > 0) ? std::min(position.x, (elapsed_time/duration)*position.x) : std::max(position.x, (elapsed_time/duration)*position.x),
        (position.y > 0) ? std::min(position.y, (elapsed_time/duration)*position.y) : std::max(position.y, (elapsed_time/duration)*position.y)
    });
    std::cout << node_insert->getPosition().x << " "<< node_insert->getPosition().y << "\n";

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
    if (isDone || toVisit.empty() && !curNode || Graph_Scene::ani == None) return;
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
    if (isDone || !targetNode || Graph_Scene::ani == None) return;
    elapsed_time += deltaTime;

    targetNode->highlight(RED);
    for (auto* edge : Graph_Scene::Edges) {
        if (edge->getFrom() == targetNode || edge->getTo() == targetNode) {
            edge->Draw(edge->getFrom()->GetHighlightColor2(RED, 30.0), 1);
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
    std::cout << "Construct Ani_Dijkstra\n";
}
Ani_Dijkstra::~Ani_Dijkstra() { 
    cur = nullptr;
    delete cur;
    curEdge = nullptr;
    delete curEdge;
}

void Ani_Dijkstra::updateAnimations(float deltaTime) {
    if (isDone || history.empty() || !isPrerunDone || Graph_Scene::ani == None) return;

    switch (Graph_Scene::ani_state) {
        case animation_state::Pause:
            break;

        case animation_state::Backward:
            if (currentStep > 0) currentStep--;
            Graph_Scene::ani_state = animation_state::Pause;
            break;

        case animation_state::Forward:
            if (currentStep + 1 < (int)history.size()) currentStep++;
            Graph_Scene::ani_state = animation_state::Pause;
            break;

        case animation_state::Continue:
            break;

        case animation_state::FirstState:
            currentStep = 1;
            Graph_Scene::ani_state = animation_state::Pause;
            break;

        case animation_state::FinalState:
            currentStep = history.size() - 1;
            Graph_Scene::ani_state = animation_state::Pause;
        default:
            break;         
    }

    if (Graph_Scene::ani_state != animation_state::Pause) elapsed_time += deltaTime;

    if (elapsed_time >= duration) {
        std::cout << "Step " << currentStep << " is done!\n";
        if (++currentStep >= history.size()) {
            isDone = true;
            Graph_Scene::ani = None;
            std::cout << "Animation of Dijkstra is completed!\n";
            return;
        }
        elapsed_time = 0;
    }

    const auto& snap = history[currentStep];
    cur = snap.cur;
    visited = snap.visited;
    mp = snap.mp;
    dist = snap.dist;
    curEdge = snap.curEdge;
    Graph_Scene::pq = snap.pq;

    // Highlight curEdge
    if (curEdge) {
        curEdge->Draw(cur->GetHighlightColor2(cur->colorNode, 30.0), 1);
        if (curEdge->getTo() == cur) static_cast<GraphNode*>(curEdge->getFrom())->highlight(cur->colorNode);
        else static_cast<GraphNode*>(curEdge->getTo())->highlight(cur->colorNode);
    }
    // Highlight nodes
    for (auto* node : Graph_Scene::graphNodes) {
        if (node) {
            std::string text = (dist[node->val] == INF) ? "INF" : std::to_string(dist[node->val]);
            DrawText(text.c_str(), node->getPosition().x - 10, node->getPosition().y - 50, 15, node->colorNode);
            if (visited.find(node) != visited.end() && node != cur) {
                node->highlight(GREEN); 
            } 
            else if (cur && node == cur) {
                node->highlight(cur->colorNode); 
            }
        }
    }
}

void Ani_Dijkstra::play() {}

void Ani_Dijkstra::updateTarget(GraphNode* start) {
    if (isDone && Graph_Scene::ani == None) {
        std::cout << "Starting prerun for Dijkstra\n";
        prerun(start);
    }
}

void Ani_Dijkstra::prerun(GraphNode* start) {
    history.clear();
    dist.clear();
    pq = {};
    visited.clear();
    mp.clear();
    for (auto* node : Graph_Scene::graphNodes) {
        dist[node->val] = INF;
    }
    dist[start->val] = 0;
    pq.push({0, start});
    GraphNode* cur_local = nullptr;
    Edge* curEdge_local = nullptr;
    std::unordered_set<GraphNode*> visited_local;
    std::unordered_map<GraphNode*, std::unordered_set<GraphNode*>> mp_local;
    std::unordered_map<int, int> dist_local = dist;

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        if (visited_local.count(u)) {
            pq.pop();
            continue;
        }
        cur_local = u;
        history.push_back({nullptr, visited_local, mp_local, dist_local, nullptr, pq});
        visited_local.insert(u);
        pq.pop();
        history.push_back({u, visited_local, mp_local, dist_local, nullptr, pq});
        for (auto* v : u->getAdj()) {
            if (mp_local[u].count(v)) continue;

            Edge* e = nullptr;
            for (auto* edge : Graph_Scene::Edges) {
                if ((edge->getFrom() == u && edge->getTo() == v) || (edge->getFrom() == v && edge->getTo() == u)) {
                    e = edge; break;
                }
            }
            history.push_back({u, visited_local, mp_local, dist_local, e, pq});

            mp_local[u].insert(v);
            mp_local[v].insert(u);

            if (dist_local[v->val] > dist_local[u->val] + e->weight) {
                dist_local[v->val] = dist_local[u->val] + e->weight;
                pq.push({dist_local[v->val], v});
            }

            // Store snapshot after each edge relax
            history.push_back({u, visited_local, mp_local, dist_local, e, pq});
        }
    }
    history.push_back({nullptr, visited_local, mp_local, dist_local, nullptr, pq});

    cur = nullptr;
    curEdge = nullptr;
    currentStep = 0;
    isDone = false;
    isPrerunDone = true;
    Graph_Scene::ani = DijkstraRunning;
    Graph_Scene::ani_state = animation_state::Continue;
    std::cout << "Running Dijkstra\n";
    std::cout << "Dijkstra is included " << history.size() - 1 << " steps!\n";
}
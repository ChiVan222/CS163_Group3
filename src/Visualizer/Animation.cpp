#include "Animation.h"
#include <iostream>

Animations::Animations(float duration) : isDone(false), elapsed_time(0), duration(duration) {}

Ani_LinkedListTraversal::       Ani_LinkedListTraversal(float duration, SinglyLinkedList::Node* cur, Vector2 position, int radius)
    : Animations(duration), position(position), radius(radius), cur(cur) {
    Nodes.clear();
    Nodes.reserve(100);
    Nodes.push_back(SinglyNode(cur, position, radius));
}

Ani_LinkedListTraversal::Ani_LinkedListTraversal() : Animations(0), cur(nullptr) {}

void Ani_LinkedListTraversal::updateAnimations(float deltaTime) {
    if (isDone) 
    {
        return;
    }
    elapsed_time += deltaTime;
    if (Nodes.empty()) return;
    Nodes.back().SetPrimaryHighLight();
    if (elapsed_time >= duration) {
        if (cur && cur->next) {
            if (Nodes.size() >= 2) Nodes[Nodes.size() - 2].SetNullHighLight();
            Nodes.back().SetSecondaryHighLight();
            cur = cur->next;
            position.x = position.x + 2 * radius + 20;
            Nodes.push_back(SinglyNode(cur, position, radius));
            if (Nodes.size() >= 2) {
                Edges.push_back(Edge(&Nodes[Nodes.size() - 2], &Nodes.back()));
            }
        } else {
            isDone = true;
        }
        elapsed_time = 0;
    }
}

void Ani_LinkedListTraversal::play() {
    elapsed_time = 0;
    isDone = false;
}

void Ani_LinkedListTraversal::Draw() {
    for (int i = 0; i < Nodes.size(); i++) {
         Nodes[i].Draw();
    }
    for (int i = 0; i < Edges.size();) {
        if(Edges[i].Draw())
        { 
            i++;
        }
        else{
           Edges.erase(Edges.begin()+i);
        }
    }

    
}

Ani_LinkedListTraversal& Ani_LinkedListTraversal::operator=(Ani_LinkedListTraversal&& other) noexcept {
    if (this == &other) return *this;
    Nodes.clear();
    Edges.clear();
    cur = other.cur;
    elapsed_time = other.elapsed_time;
    duration = other.duration;
   isDone= other.isDone;
    Nodes = std::move(other.Nodes);
    Edges = std::move(other.Edges);
    other.Nodes.clear();
    other.Edges.clear();
    radius = other.radius;
    position = other.position;
    other.cur = nullptr;
    return *this;
}
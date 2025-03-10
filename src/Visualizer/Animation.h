#pragma once
#include "../DataStructures/SinglyLinkedList/SinglyLinkedList.h"
#include "SinglyNode.h"
#include "Edge.h"
#include <vector>

class Animations {
protected:
    float elapsed_time;
    float duration;
    bool isDone;
public:
    virtual void updateAnimations(float deltaTime) = 0;
    virtual void play() = 0;
    virtual void Draw() = 0;
    explicit Animations(float duration);
};

class Ani_LinkedListTraversal : public Animations {
private:
    SinglyLinkedList::Node* cur;
    std::vector<SinglyNode> Nodes;
    std::vector<Edge> Edges;
    float radius;
    Vector2 position;
public:
    Ani_LinkedListTraversal();
    Ani_LinkedListTraversal(float duration, SinglyLinkedList::Node* cur, Vector2 position, int radius);
    void updateAnimations(float deltaTime) override;
    void play() override;
    void Draw() override;
    Ani_LinkedListTraversal& operator=(Ani_LinkedListTraversal&& other) noexcept;
};
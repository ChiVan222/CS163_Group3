#pragma once
#include "Animation.h"
#include "GraphNode.h"
#include "Edge.h"

class Ani_GraphInsert : public Animations {
public:
    Ani_GraphInsert();
    Ani_GraphInsert(float duration, int value, float radius, Vector2 position);
    void updateAnimations(float deltaTime) override;
    void updateTarget(GraphNode*& node);

private:
    int value;
    float radius;
    Vector2 position, src_pos;
    GraphNode* node_insert;
    void play(GraphNode*& node);
    void play() override;
};
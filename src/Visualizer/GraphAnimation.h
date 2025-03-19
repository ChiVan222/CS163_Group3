#pragma once
#include "Animation.h"
#include "GraphNode.h"
#include "Edge.h"

class Ani_GraphInsert : public Animations {
private:
    float radius;
    Vector2 position;
    int value;
    GraphNode* node_insert;
    Vector2 src_pos;
public:
    Ani_GraphInsert(float duration, int value, float radius, Vector2 position);
    Ani_GraphInsert();
    void updateAnimations(float deltaTime) override;
    void play() override;
    void updateTarget(int value, float radius, Vector2 position);
};
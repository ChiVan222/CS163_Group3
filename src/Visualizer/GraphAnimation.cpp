#include "GraphAnimation.h"
#include "Scene.h"
#include <iostream>

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
        cout << "Update target " << value << "\n";
        Graph_Scene::ani = Inserting;
        this->value = node->val;
        this->radius = node->getRadius();
        this->position = node->getPosition();
        play(node);
    }
}

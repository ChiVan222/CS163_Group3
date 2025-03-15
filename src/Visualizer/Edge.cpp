#include "Edge.h"
#include <raylib.h> 
#include <iostream> 
#include "Scene.h"
Edge::Edge(PolyNode* from , PolyNode* to) : from(from), to(to),isDraw(false)
{
}
bool Edge::Draw()
{
    if(from && to)
    {
        DrawLineBezier(Vector2({from->getPosition().x+Singly_Scene::Node_radius,from->getPosition().y})
            , Vector2({to->getPosition().x-Singly_Scene::Node_radius,to->getPosition().y}),size,WHITE); 
        return true;
    }
    return false;
}
PolyNode* Edge::getFrom()
{
    return from;
}
PolyNode* Edge::getTo(){
    return to;

} 
int Edge::getsize()
{
    return size;
}
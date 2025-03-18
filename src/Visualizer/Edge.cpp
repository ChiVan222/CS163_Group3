#include "Edge.h"
#include <raylib.h> 
#include <iostream> 
#include "Scene.h"
#include <math.h> 
Edge::Edge(PolyNode* from , PolyNode* to) : from(from), to(to),isDraw(false)
{
}
bool Edge::Draw()
{
    if(from && to)
    {
        // float theta = PI+ atan2((from->getPosition().y - to->getPosition().y),(from->getPosition().x - to->getPosition().x));  
        // Vector2 cpos =   Vector2({Singly_Scene::Node_radius*cos(theta)+from->getPosition().x,Singly_Scene::Node_radius*sin(theta)+from->getPosition().y}); 
        // Vector2 dpos =   Vector2({Singly_Scene::Node_radius*cos(theta)+to->getPosition().x,Singly_Scene::Node_radius*sin(theta)+to->getPosition().y}); 
       
       
        float theta = atan2(to->getPosition().y - from->getPosition().y, 
                    to->getPosition().x - from->getPosition().x);

Vector2 cpos = Vector2({Singly_Scene::Node_radius * cos(theta) + from->getPosition().x,
                         Singly_Scene::Node_radius * sin(theta) + from->getPosition().y});

Vector2 dpos = Vector2({to->getPosition().x - Singly_Scene::Node_radius * cos(theta),
                         to->getPosition().y - Singly_Scene::Node_radius * sin(theta)});
       
        // DrawLineBezier(Vector2({from->getPosition().x+Singly_Scene::Node_radius,from->getPosition().y})
        //     , Vector2({to->getPosition().x-Singly_Scene::Node_radius,to->getPosition().y}),size,WHITE); 
        // DrawLineBezier(cpos,dpos,size,WHITE); 
        DrawLineEx(cpos,dpos,size,WHITE);
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
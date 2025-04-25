#include "Edge.h"
#include <raylib.h> 
#include <iostream> 
#include "Scene.h"
#include <math.h> 
Edge::Edge(PolyNode* from , PolyNode* to) : from(from), to(to),isDraw(false)
{
    color = WHITE; 
}
bool Edge::Draw(Color color, int flat)
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
        DrawLineEx(cpos,dpos,size,color);
        if (flat == 1) {
            Vector2 pos1 = getFrom()->getPosition();
            Vector2 pos2 = getTo()->getPosition();
            Vector2 midPoint = {(pos1.x + pos2.x) / 2, (pos1.y + pos2.y) / 2};
            float angle = atan2(pos2.y - pos1.y, pos2.x - pos1.x);
            float distance = sqrt(pow(pos2.x - pos1.x, 2) + pow(pos2.y - pos1.y, 2));
            float offsetDistance = distance / 20;
            Vector2 offset = {offsetDistance * cos(angle + PI / 2), offsetDistance * sin(angle + PI / 2)};
            const char* weightText = TextFormat("%d", weight);
            int textWidth = MeasureText(weightText, 20);
            DrawText(weightText, midPoint.x + offset.x - textWidth / 2, midPoint.y + offset.y, 20, WHITE);
        }
        return true;
    }
    return false;
}
bool Edge::TrieDraw(){
    if(from && to){
        float theta = atan2(to->getPosition().y - from->getPosition().y,to->getPosition().x - from->getPosition().x);

        Vector2 cpos = Vector2({Trie_Scene::Node_radius * cos(theta) + from->getPosition().x,Trie_Scene::Node_radius * sin(theta) + from->getPosition().y});

        Vector2 dpos = Vector2({to->getPosition().x - Trie_Scene::Node_radius * cos(theta),to->getPosition().y - Trie_Scene::Node_radius * sin(theta)});

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
void Edge::setSize(int nsize)
{
    size= nsize; 
}
Color Edge::getColor()
{
     return color;
}
void Edge::setColor(Color ncolor)
{
    color = ncolor; 
}

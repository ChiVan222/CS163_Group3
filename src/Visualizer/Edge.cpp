#include "Edge.h"
#include <raylib.h> 
#include <iostream> 
Edge::Edge(PolyNode* from , PolyNode* to) : from(from), to(to)
{
    
}
bool Edge::Draw()
{
    if(from && to)
    {
        DrawLine(from->getPosition().x + from->getRadius(), from->getPosition().y, to->getPosition().x-to->getRadius(), to->getPosition().y, WHITE); 
        return true;
    }
    return false;
}

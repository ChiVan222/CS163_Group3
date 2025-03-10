#include "Edge.h"
#include <raylib.h> 
Edge::Edge(PolyNode* from , PolyNode* to) : from(from), to(to)
{
    
}
void Edge::Draw()
{
    DrawLine(from->getPosition().x + from->getRadius(), from->getPosition().y, to->getPosition().x- to->getRadius(), to->getPosition().y, WHITE); 
}
#include "PolyNode.h"
PolyNode:: PolyNode(Vector2 pos,float radius): position(pos), radius(radius)
{
    highlight = Null;
}   
void PolyNode::SetPrimaryHighLight()
{
    highlight = Primary; 
}
void PolyNode::SetSecondaryHighLight()
{ 
    highlight = Secondary;
}
void  PolyNode::SetNullHighLight()
{ 
    highlight = Null; 
}
Vector2 PolyNode::getPosition()
{
    return position;
}
float PolyNode::getRadius()
{
     return radius;
}

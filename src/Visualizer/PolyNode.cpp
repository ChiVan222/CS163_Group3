#include "PolyNode.h"
#include "Scene.h"
 PolyNode:: PolyNode(Vector2 pos,float radius): position(pos), radius(radius)
 {
     highlight = Null;
}
Color PolyNode::colorNode={243,80,0,255};
void PolyNode::DrawNode(){
        float outline_thickness = 6.0f;
        DrawCircle(position.x, position.y, radius + outline_thickness, HightLight);
        DrawCircle(position.x, position.y, radius, colorNode);

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
void PolyNode::SetPosition(Vector2 newpos){
    position = newpos;
}

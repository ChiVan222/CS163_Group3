#include "PolyNode.h"
#include "Scene.h"
#include <raymath.h>
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
Color PolyNode:: GetHighlightColor(Color color, float factor) {
    Color highlight;
    highlight.r = (unsigned char)Clamp(color.r + (255 - color.r) * factor, 0, 255);
    highlight.g = (unsigned char)Clamp(color.g + (255 - color.g) * factor, 0, 255);
    highlight.b = (unsigned char)Clamp(color.b + (255 - color.b) * factor, 0, 255);
    highlight.a = color.a;
    return highlight;
}

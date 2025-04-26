#include "PolyNode.h"
#include "Scene.h"
#include <raymath.h>
#include <iostream>
 PolyNode:: PolyNode(Vector2 pos,float radius): position(pos), radius(radius)
 {
     highlight = Null;
}
Color PolyNode::colorNode={243,80,0,255};
void PolyNode::DrawNode(){
        float outline_thickness = 4.0f;
        if(highlight==Null){
            DrawCircle(position.x, position.y, radius + outline_thickness, HightLight);

        }
        else if (highlight!=Null && Scene::isDarkMode){
            DrawCircle(position.x, position.y, radius + outline_thickness, darkSpecialHightLight);

        }
        else if (highlight!=Null && Scene::isDarkMode==false){
            DrawCircle(position.x, position.y, radius + outline_thickness, lightSpecialHighLight);

        }
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
Color PolyNode::GetHighlightColor2(Color color, float hueShiftDegrees) {
    Vector3 hsv = ColorToHSV(color);  
    hsv.x += hueShiftDegrees;

    if (hsv.x > 360.0f) hsv.x -= 360.0f;
    if (hsv.x < 0.0f) hsv.x += 360.0f;

    Color result = ColorFromHSV(hsv.x,hsv.y,hsv.z);
    result.a = color.a; 
    return result;
}

std::pair<Color, Color> PolyNode::GetHighlightColors3(Color original) {
    Vector3 hsv = ColorToHSV(original);

    float accentHue = fmodf(hsv.x + 90.0f, 360.0f);
    float midHue    = fmodf((hsv.x + accentHue) / 2.0f, 360.0f); 

    float accentSat = Clamp(hsv.y * 0.9f, 0.0f, 1.0f);  
    float accentVal = Clamp(hsv.z * 1.1f, 0.0f, 1.0f);  

    float midSat = Clamp(hsv.y * 0.95f, 0.0f, 1.0f);
    float midVal = Clamp(hsv.z * 1.05f, 0.0f, 1.0f);

    Color primary   = ColorFromHSV( accentHue, accentSat, accentVal );
    Color secondary = ColorFromHSV( midHue, midSat, midVal );

    primary.a   = original.a;
    secondary.a = original.a;

    return { primary, secondary };
}

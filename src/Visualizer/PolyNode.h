#pragma once
#include <raylib.h>
#include <utility>
class PolyNode
{ 
    protected :  
        typedef enum Highlight{ 
                Null, 
                Primary, 
                Secondary 
        } HighLight;
        HighLight highlight;
        float radius;           //=25.0f 
        Vector2 position; 
        Color darkSpecialHightLight{85,253,200,255};
        Color lightSpecialHighLight{0,0,0,255};
        Color HightLight{255,255,255,255};

   public : 
   static Color colorNode;
    virtual bool Draw() =0 ; 
    explicit PolyNode(Vector2 pos,float radius);  
    void SetPrimaryHighLight();  
    void SetSecondaryHighLight();  
    void SetNullHighLight(); 
    void DrawNode();
    Vector2 getPosition(); 
    void SetPosition(Vector2 newpos);
    float getRadius();
    Color GetHighlightColor(Color color, float factor);
    Color GetHighlightColor2(Color color, float hueShiftDegrees);
    std::pair<Color,Color> GetHighlightColors3(Color original); 
}; 
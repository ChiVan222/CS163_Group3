#pragma once
#include <raylib.h>
class PolyNode
{ 
    protected :  
        typedef enum Highlight{ 
                Null, 
                Primary, 
                Secondary 
        } HighLight;
        HighLight highlight;
        float radius;   
        Vector2 position; 
   public : 
    virtual bool Draw() =0 ; 
    explicit PolyNode(Vector2 pos,float radius);  
    void SetPrimaryHighLight();  
    void SetSecondaryHighLight();  
    void SetNullHighLight(); 
    Vector2 getPosition(); 
    void SetPosition(Vector2 newpos);
    float getRadius();
}; 
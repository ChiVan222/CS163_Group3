#pragma once 
#include <raylib.h> 
class Button 
{
  
  public : 
    Button(const char* imgpath, Vector2 pos, float scale); 
    ~Button();
    void Draw();     
    bool IsHovered(Vector2 mousePos);
  private : 
    typedef enum HighLight{
      None, 
      HighLighting
     } HighLight; 

    HighLight isHovered; 
    Texture2D texture; 
    Vector2 position; 

}; 
#pragma once 
#include <raylib.h> 
#include "Ultility.h"
class Button 
{
  public : 
    Button(const char* imgpath, Vector2 pos,Vector2 rect, const char* title); 
    ~Button();
    Button(); 
    void Draw();     
    void DrawButtonText(Vector2 textpos); 
    void DrawButtonText_center();
    void DrawButtonText_below(); 
    bool IsHovered(Vector2 mousePos);
    const char* get_title() ; 
    Texture2D get_texture(); 
    Vector2 get_position();
    Vector2 get_rectangle();
  protected : 
    typedef enum HighLight{
      None, 
      HighLighting
     } HighLight;   
    const char* title;  
    HighLight isHovered; 
    Texture2D texture; 
    Vector2 position; 
    Vector2 rect; 
}; 
class SceneButton: public Button //Button for switching scenes 
{ 
 
  private :  
    Scenes bScenes;
  public : 
    Scenes getButtonScenes();  
    SceneButton(const char* imgpath, Vector2 pos,Vector2 rect, const char* title,Scenes bScenes);
    ~SceneButton(){};
}; 
class InputButton: public Button
{ 
  private :

  public : 
    
};
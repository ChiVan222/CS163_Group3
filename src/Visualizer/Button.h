#pragma once 
#include <raylib.h> 
#include "UI.h"
class Button 
{
  public : 
    Button(const char* imgpath, Vector2 pos,Vector2 rect, const char* title); 
    ~Button();
    void Draw();     
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
    UI::Scenes bScenes;
  public : 
    UI::Scenes getButtonScenes();  
    SceneButton(const char* imgpath, Vector2 pos,Vector2 rect, const char* title, UI::Scenes bScenes);
}; 
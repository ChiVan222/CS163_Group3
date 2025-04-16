#pragma once 
#include <raylib.h> 
#include "Ultility.h"
#include <functional>
class Button 
{
  public : 
    Button(const char* imgpath, Vector2 pos,Vector2 rect, const char* title); 
    ~Button();
    Button(); 
    std::function<void()> OnClick;
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
class SettingButton: public Button{
  public:
    SettingButton(Vector2 pos, Vector2 rect1);
    void SettingDraw();
 };

 class Slider:public Button{
  public:
    int type;
    float spacing ;
    static float red ;
    static float green ;
    static float blue ;

  public:
    Slider(Vector2 pos, Vector2 rect1, int t);
    void SliderDraw();
};

class ControlButton: public Button{
  public:
    int inc;
  public:
    ControlButton(Vector2 pos, Vector2 rect1, int t);
    void ButtonDraw();

};

class Spinner: public Button{
  public:
    display dis;
    int choices = 2;
    int current;
  public:
    Spinner(display d, Vector2 pos, Vector2 rect1,const char* title,  int crt);
    void spinnerDraw();
    void DrawTextSpinner(Font curentFont);
    void ChangeTitle(const char* newtitle);


};

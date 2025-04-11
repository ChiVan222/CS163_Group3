#include "Button.h"
#include <cmath>
#include "UI.h"
Button::Button(const char* imgpath, Vector2 pos, Vector2 rect,const char* title):position(pos), title(title), rect(rect){
     Image img =  LoadImage(imgpath); 
     int oWidth =img.width;
     int oHeight = img.height;   
     float scaleX = (float)rect.x/oWidth; 
     float scaleY = (float)rect.y/oHeight; 
     float scale = fmin(scaleX,scaleY);
     int nWidth = static_cast<int>(oWidth*scale);
     int nHeight = static_cast<int>(oHeight*scale);
     ImageResize(&img,nWidth,nHeight);
     texture =  LoadTextureFromImage(img);
     UnloadImage(img);
     isHovered = None;
}
Button::Button()
{
    position.x =0 ;
    position.y = 0 ; 
    title = "";
}
Button::~Button(){ 
    UnloadTexture(texture); 
}
SceneButton::SceneButton(const char* imgpath, Vector2 pos,Vector2 rect, const char* title, Scenes bScenes)
: Button(imgpath,pos,rect,title), bScenes(bScenes){}

void Button::Draw()
{ 
    Color borderColor = isHovered == None? RED : GREEN;
    Color imageColor  = isHovered == None? GRAY : WHITE;
    if(!IsTextureValid(texture))
    {
        Image img = GenImageColor(100, 100, GRAY);
        texture = LoadTextureFromImage(img);
        UnloadImage(img);
    }
    Rectangle src = { 0, 0, (float)texture.width, (float)texture.height };  
    Rectangle dest = {position.x, position.y, (float)rect.x, (float)rect.y }; 
    DrawTexturePro(texture, src, dest, Vector2({0, 0}), 0.0f, imageColor);
    DrawRectangleLinesEx(Rectangle({position.x, position.y, (float)rect.x, (float)rect.y}),3,borderColor);
}
void Button::DrawButtonText(Vector2 textpos)
{
    DrawText(title, textpos.x, textpos.y, 20, WHITE);
}
void Button::DrawButtonText_below()
{
    DrawButtonText(Vector2({position.x,position.y + 10 + rect.y}));
}
void Button::DrawButtonText_center()
{ 

    int textWidth = MeasureText(title, UI::fontsize);
    int textHeight = UI::fontsize;

    float textX = position.x + (rect.x - textWidth) / 2;
    float textY = position.y + (rect.y - textHeight) / 2;

    DrawButtonText(Vector2({textX,textY}));
}
bool Button :: IsHovered(Vector2 mousePos)
{
    Rectangle rect2 =  {position.x,position.y, rect.x,rect.y};
   if(CheckCollisionPointRec(mousePos,rect2))
   {
        isHovered = HighLighting; 
        return true; 
   }else 
   {
    isHovered =None;
   }
   return false; 
}


const char* Button::get_title() 
{
    return title; 
}
Texture2D Button::get_texture()
{
    return texture; 
}
Vector2 Button::get_position()
{
  return position;
}
Vector2 Button::get_rectangle()
{
  return rect; 
}
Scenes SceneButton::getButtonScenes()
{
    return bScenes; 
}

Switch::Switch(Vector2 pos, Vector2 rect1):Button() {
    position = pos;
    rect = rect1;
    cradius = rect.y / 2;
    centerC.x = position.x + cradius;
    centerC.y = position.y + rect.y / 2;
    isOn = false;
}

void Switch::SwitchDraw(){
    Color defaultColor = {240,240,240, 255};
    if (isOn){
        DrawRectangleRounded((Rectangle){position.x-5.0f, position.y-5.0f, (float)rect.x+10.0f, (float)rect.y+10.0f}, 1, 1000, BLACK);
    }
    
    else{
        DrawRectangleRounded((Rectangle){position.x-5.0f, position.y-5.0f, (float)rect.x+10.0f, (float)rect.y+10.0f}, 1, 1000, LIGHTGRAY);
    }
    DrawCircle(centerC.x, centerC.y, cradius, WHITE);
    
}
    
bool Switch::mode(Vector2 mousePos){
    Rectangle rect2 =  {position.x,position.y, rect.x,rect.y};
    if(CheckCollisionPointRec(mousePos,rect2) && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)))
    {
        return true;
    }
    else return false;
}
    
void Switch::setCircle(Vector2 newPos){
    centerC= newPos;
}
    
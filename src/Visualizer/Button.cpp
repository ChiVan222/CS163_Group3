#include "Button.h"
#include <cmath>
#include "UI.h"
#include "raygui.h"
#include <iostream>

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
void Button::DrawButtonText(Vector2 textpos, int fontSize)
{
    DrawText(title, textpos.x, textpos.y, fontSize, WHITE);
}
void Button::DrawButtonText_below(int fontSize)
{
    DrawButtonText(Vector2({position.x,position.y + 10 + rect.y}), fontSize);
}
void Button::DrawButtonText_center()
{ 
    int textWidth = MeasureText(title, UI::fontsize);
    int textHeight = UI::fontsize;

    float textX = position.x + (rect.x - textWidth) / 2;
    float textY = position.y + (rect.y - textHeight) / 2;

    DrawButtonText(Vector2({textX,textY}), 30);
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
float Slider::red = 243.0f;
float Slider::green = 80.0f;
float Slider::blue = 0.0f;
SettingButton::SettingButton(Vector2 pos, Vector2 rect1):Button() {
    position = pos;
    rect = rect1;

}
void Button::setPositionRect(Vector2 newPos, Vector2 newRect)
{
    position = newPos;
    rect = newRect;
}
void Button::setPositionText(Vector2 newPos, Texture2D newText) {
    position = newPos;
    texture = newText;
}


void SettingButton::SettingDraw(){
    std::cout<< "Draw setting"<<"\n";
    Image img =  LoadImage("../assets/Images/icon_setting.png");
    texture =  LoadTextureFromImage(img);
    UnloadImage(img);
    Rectangle btnBounds = {position.x, position.y, (float)texture.width, (float)texture.height};
    DrawTexture(texture, btnBounds.x, btnBounds.y, WHITE);
}

Slider::Slider(Vector2 pos, Vector2 rect1, int t){
    position = pos;
    rect = rect1;
    type =t;
}
void Slider::SliderDraw(){
         if (type==1)
             GuiSlider((Rectangle){ position.x, position.y, rect.x, rect.y }, NULL , NULL, &red, 0, 255);
        else if (type==2)
             GuiSlider((Rectangle){ position.x, position.y, rect.x, rect.y }, NULL , NULL, &green, 0, 255);
         else if(type==3)
             GuiSlider((Rectangle){ position.x, position.y, rect.x, rect.y }, NULL , NULL, &blue, 0, 255);
     }
    
    
    
ControlButton::ControlButton(Vector2 pos, Vector2 rect1, int t){
        position = pos;
        rect = rect1;
        inc = t;
}

void ControlButton::ButtonDraw() {
       // Nền nút
        DrawRectangle(position.x, position.y, rect.x, rect.y, {89, 89, 89, 255});

        // Tam giác (mũi tên)
        Vector2 A, B, C;
    
        if (inc == 1) {
            // Mũi tên sang phải
            A = {position.x + rect.x - 8.0f, position.y + rect.y / 2.0f};
       B = {position.x + 7.0f, position.y + 7.0f};
            C = {position.x + 7.0f, position.y + rect.y - 7.0f};
            DrawTriangle(A, B, C, {239, 229, 208, 255});
        }
        else {
            // Mũi tên sang trái
            A = {position.x + 8.0f, position.y + rect.y / 2.0f};
            B = {position.x + rect.x -7.0f, position.y + 7.0f};
            C = {position.x + rect.x -7.0f, position.y + rect.y - 7.0f};
            DrawTriangle(A, C, B, {239, 229, 208, 255});
         }
}

Spinner::Spinner(display d,Vector2 pos, Vector2 rect1,const char* t,  int crt ){
        dis =d;
        position=pos;
        rect = rect1;
        current = crt;
        title=t;
}
void Spinner::spinnerDraw(){
    DrawRectangle(position.x, position.y, rect.x, rect.y,{143,141,141,255});
}
void Spinner::ChangeTitle(const char* newtitle){
    title=newtitle;
}
void Spinner::DrawTextSpinner(Font currentFont) {
    float spacing = 1.0f;
    int fontSize = rect.y * 0.5f;
        
    Vector2 textSize = MeasureTextEx(currentFont, title, (float)fontSize, spacing);
    Vector2 textPos = {
        position.x + (rect.x - textSize.x) / 2.0f,
        position.y + (rect.y - textSize.y) / 2.0f
    };
        
    DrawTextEx(currentFont, title, textPos, (float)fontSize, spacing, WHITE);
}


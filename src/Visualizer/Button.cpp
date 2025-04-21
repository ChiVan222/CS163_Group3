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
float Slider::red = 243.0f;
float Slider::green = 80.0f;
float Slider::blue = 0.0f;
SettingButton::SettingButton(Vector2 pos, Vector2 rect1):Button() {
    position = pos;
    rect = rect1;

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
CodeBlock::CodeBlock():Button(){};
CodeBlock::CodeBlock(Vector2 pos, Vector2 rect1){
    position =pos;
    rect = rect1;
    font = LoadFont("../assets/Font/AnkaCoder.ttf");
    spacing = 1.0f;
    scrollY = 0.0f;
    fontSize = rect.y/20.0f;
    lineSpacing = fontSize + 5.0f;
}

void CodeBlock::Draw() {
    DrawRectangleRec({position.x, position.y, rect.x, rect.y}, LIGHTGRAY);
    float x = position.x + 10;
    float y = position.y + UI::wHeight/20.0f + 10 - scrollY;

    DrawTitle();
    for (auto& line : lines) {
        if (y + lineSpacing > position.y && y < position.y + rect.y) {
            DrawTextEx(font, line.c_str(), {x, y}, fontSize, spacing, WHITE);
        }
        y += lineSpacing;
    }

}
void CodeBlock::DrawTitle(){
    Color color,textColor, lineColor;
    if (Scene::isDarkMode) {
        color = darkBlock;
        lineColor = WHITE;
        textColor = BLACK;
    }
    else{
        color = lightBlock;
        lineColor = BLACK;
        textColor = WHITE;
    }
    float lineThick = 4.0f;
    float titleHeight = UI::wHeight / 20.0f ;
    Rectangle innerRect = {
        position.x ,
        position.y + lineThick / 2,
        rect.x - lineThick/2,
        titleHeight - lineThick/2
    };
    
    DrawRectangleRec(innerRect, color);
    
    DrawRectangleLinesEx({position.x, position.y, rect.x, titleHeight}, lineThick, lineColor);
    float textFontSize= titleHeight*0.5f;
    const char* titleText = "CODE BLOCK";
    Vector2 titleSize = MeasureTextEx(Scene::currentFont, titleText, textFontSize, spacing);
    Vector2 titlePos = {position.x+(rect.x-titleSize.x)/2.0f, position.y + (UI::wHeight/20.0f-titleSize.y)/2.0f};
    DrawTextEx(Scene::currentFont, titleText, titlePos, fontSize, spacing, textColor);
}
void CodeBlock::Scroll(float amount) {
    scrollY += amount;
    if (scrollY < 0) scrollY = 0;
}

void CodeBlock::SetLines(const std::vector<std::string>& newLines) {
    lines.clear();
    for (const std::string& rawLine : newLines) {
        WrapAndAddLine(rawLine);
    }
}

void CodeBlock::WrapAndAddLine(const std::string& rawLine) {
    size_t indentPos = rawLine.find_first_not_of(" \t");
    std::string indent = (indentPos != std::string::npos) ? rawLine.substr(0, indentPos) : "";
    if (font.texture.id == 0) {
        font = GetFontDefault();
    }
    std::istringstream stream(rawLine);
    std::string word;
    std::string currentLine = indent;
    float maxWidth = rect.x - 20; 

    while (stream >> word) {
        std::string testLine = currentLine.empty() ? word : currentLine + " " + word;
        Vector2 size = MeasureTextEx(font, testLine.c_str(), fontSize, spacing);

        if (size.x > maxWidth) {
            if (!currentLine.empty()) lines.push_back(currentLine);
            currentLine = indent + word;  
        } else {
            currentLine = testLine;
        }
    }

    if (!currentLine.empty()) lines.push_back(currentLine);
}
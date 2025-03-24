#include "UI.h"
#include <iostream> 
#include <math.h>
float UI::time = 0.0f;
Vector2 UI::mousePos = {0, 0};
Texture2D UI::background;
float UI::fontsize =0.0f;
void UI::UILoadFont()
{
   mFont = LoadFont("../assets/Fonts/fonts.ttf"); 
}
void UI::UIUnLoadFont()
{
   UnloadFont(mFont);
}
Font UI::getFont()
{
    return mFont; 
}
void UI::DrawFadingText(float time, int x, int y, int fontsize,const char* text)
{
    float alpha  = (sin(time*4.0f)+1.0f)/2 ; 
    Color textColor = {255,255,255,(unsigned char)(alpha*255)}; 
    DrawText(text, x,y,fontsize,textColor); 
}
UI::UI():  mFont(GetFontDefault())
{
    fontsize = mFont.baseSize;
}
void UI::
run()
{

    InitWindow(wWidth, wHeight, "Hello, World!");
    UI::background = LoadTexture("../assets/Images/background.png");
    SetTargetFPS(mFPS);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    scene_manager = new SceneManager();
    while (!WindowShouldClose())
    {
        time = GetTime();
        BeginDrawing();
        mousePos  = GetMousePosition(); 
        DrawFPS(wWidth-100,100);
        scene_manager->runScene(); 
        EndDrawing();
    }
    CloseWindow();
    return; 
}
UI::~UI()
{
    delete scene_manager;
}


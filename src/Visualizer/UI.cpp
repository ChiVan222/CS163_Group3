#include "UI.h"
#include <iostream> 
#include <math.h>
#include <rlgl.h>
#include <raymath.h>
float UI::time = 0.0f;
Vector2 UI::mousePos = {0, 0};
Texture2D UI::background;
float UI::fontsize = 0.0f;
Camera2D UI::camera = {0};
float UI::wWidth = 1920;
float UI::wHeight = 1080;

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
    camera.offset = {(float)wWidth / 2, (float)wHeight / 2};    
    camera.zoom  =1; 
    camera.target = { 0, 0 };
}
    void UI::updateCamera()
    {   
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            Vector2 delta = GetMouseDelta();
            delta = Vector2Scale(delta, -1.0f/camera.zoom);
            camera.target = Vector2Add(camera.target, delta);
        }
        float wheel = GetMouseWheelMove();
        if (wheel != 0)
        {

            Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
            camera.offset = GetMousePosition();
            camera.target = mouseWorldPos;
            float scale = 0.2f*wheel;
            camera.zoom = Clamp(expf(logf(camera.zoom)+scale), 0.125f, 64.0f);
        }
    }
void UI:: resetCamera(){
    camera.offset = {(float)wWidth / 2, (float)wHeight / 2};    
    camera.zoom  =1; 
    camera.target = { 0, 0 };
}
void UI::run()
{

    InitWindow(wWidth, wHeight, "Hello, World!");
    UI::background = LoadTexture("../assets/Images/background.png");
    initResource();
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
void UI::ChangeCameraTarget(Vector2 newtarget)
{  
    const float followSpeed = 0.05f;
    camera.offset = {(float)wWidth / 2, (float)wHeight / 2};    
    camera.target.x = Lerp(camera.target.x, newtarget.x, followSpeed);
    camera.target.y = Lerp(camera.target.y, newtarget.y, followSpeed);
}
void UI::ChangeCameraZoom(float newzoom)
{ 
     camera.zoom = newzoom; 
}
UI::~UI()
{
    delete scene_manager;
}
 
    
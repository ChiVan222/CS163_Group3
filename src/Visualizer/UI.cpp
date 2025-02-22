#include "UI.h"
#include "Button.h"
UI::UI(): cScene(Welcome), mFont(GetFontDefault())
{
}
void UI::run()
{

    InitWindow(wWidth, wHeight, "Hello, World!");
    SetTargetFPS(mFPS);
    Texture2D background = LoadTexture("../assets/Images/background.png");
    Button SinglyLinkedList("../assets/Images/SinglyLinkedList.png",Vector2({200,200}),0.7);  
    while (!WindowShouldClose())
    {
       
        float time = GetTime();
        BeginDrawing();
        Rectangle src = { 0, 0, (float)background.width, (float)background.height };
        Rectangle dest = { 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()};
        Vector2 mousePos  = GetMousePosition(); 
        switch(cScene)
        {
            case(Welcome) :
            { 
                ClearBackground(DARKBLUE);
                DrawTexturePro(background, src, dest, Vector2({0, 0}), 0.0f, WHITE);
                DrawText("DATA STRUCTURE VISUALIZATION", 200, 200, 40, WHITE);
               
                DrawFadingText(time,200,wHeight-200,30, "Press any keys to continue");
                if(GetKeyPressed()!=0)
                {
                    cScene = Menu; 
                }

            } break; 
            case(Menu) :
            { 

                ClearBackground(DARKBLUE);
                DrawText("Menu", static_cast<int>(wWidth/2), 100, 40, WHITE);
                SinglyLinkedList.Draw();
                if(SinglyLinkedList.IsHovered(mousePos))
                {
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                       cScene =  Singly;
                }
                if(GetKeyPressed()!=0)
                {
                    cScene = Welcome; 
                }
            } break; 
            case(Singly):
            { 
                ClearBackground(DARKBLUE);
                DrawText("Singly Linked List", 200, 200, 40, WHITE);
                if(GetKeyPressed()!=0)
                {
                    cScene = Menu; 
                }
            }break; 
        }
        EndDrawing();
    }
    CloseWindow();
    return; 
}
UI::Scenes UI::getScenes()
{
    return cScene; 
}

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
#include "UI.h"
#include "Button.h"
#include "SinglyNode.h"
#include <iostream> 
#include <math.h>
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
UI::UI(): cScene(Welcome), mFont(GetFontDefault()),a(),list()
{
    created = false;
}
void UI::run()
{

    InitWindow(wWidth, wHeight, "Hello, World!");
    SetTargetFPS(mFPS);
    Texture2D background = LoadTexture("../assets/Images/background.png");
    float buttonSpacing = 20; 
    int buttons_count = 4; 
    SceneButton buttons[] = {
        SceneButton("../assets/Images/SinglyLinkedList.png", Vector2({wWidth / 5 * 1, 300}),Vector2({200,200}), "Singly Linked List",Singly),
        SceneButton("../assets/Images/holder.png", Vector2({wWidth / 5 * 2, 300}),Vector2({200,200}), "Trie",Trie),
        SceneButton("../assets/Images/holder.png", Vector2({wWidth / 5 * 3, 300}),Vector2({200,200}), "Heap",Heap),
        SceneButton("../assets/Images/holder.png", Vector2({wWidth / 5 * 4, 300}),Vector2({200,200}),"Graph",Graph)
    };
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
                for(int i = 0; i <buttons_count;  i++)
                {
                    buttons[i].Draw();
                    if(buttons[i].IsHovered(mousePos))
                    {
                        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                            cScene =  buttons[i].getButtonScenes();
                    }
                }
                if(IsKeyPressed(KEY_LEFT))
                {
                    cScene = Welcome; 
                }
            } break; 
            case(Singly):
            { 
              SinglyScene();
            }break; 
            case(Trie):
            { 
                ClearBackground(DARKBLUE);
                DrawText("Trie", 200, 200, 40, WHITE);
                if(IsKeyPressed(KEY_LEFT))
                {
                    cScene = Menu; 
                }
            }break; 
            case(Graph):
            { 
                ClearBackground(DARKBLUE);
                DrawText("Graph", 200, 200, 40, WHITE);
                if(IsKeyPressed(KEY_LEFT))
                {
                    cScene = Menu; 
                }
            }break; 
            case(Heap):
            { 
                ClearBackground(DARKBLUE);
                DrawText("Heap", 200, 200, 40, WHITE);
                if(IsKeyPressed(KEY_LEFT))
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
#include "Animation.h"
#include <raylib.h>

void UI::SinglyScene() {
 
    float deltaTime = IsWindowFocused() ? GetFrameTime() : 0;
    ClearBackground(BLACK);
    DrawText("Singly Linked List", 200, 200, 40, WHITE);
    
    if (IsKeyPressed(KEY_LEFT)) {
        cScene = Menu;
        created = false;
        list.DeleteList();
        a = Ani_LinkedListTraversal();
        return; 

    }
    
    if (!created) {
        list.Insert(5);
        list.Insert(3);
        list.Insert(7);
        list.Insert(15);
        list.Insert(12);
        list.Insert(20);
        a = Ani_LinkedListTraversal(0.3, list.get_root(), Vector2({300, 300}), 20);
        created = true;
    }
    a.updateAnimations(deltaTime);
    a.Draw();
}

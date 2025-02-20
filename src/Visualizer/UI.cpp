#include <raylib.h> 
#include "UI.h"

void UI::run()
{

    InitWindow(800, 450, "Hello, World!");
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
       
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello, World!", 10, 10, 20, DARKGRAY);
        EndDrawing();
    }   

    CloseWindow();
    return; 
}
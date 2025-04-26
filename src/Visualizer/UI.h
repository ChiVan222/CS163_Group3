#pragma once
#include <raylib.h> 
#include "Scene.h"
#include "Utility.h"
class UI 
{   public :
     static float time; 
     static Texture2D background;
     static float wWidth; 
     static float wHeight; 
     static constexpr int mFPS = 60; 
     static Vector2 mousePos;
     static float fontsize; 
     static Camera2D camera;
     static Font mFont;

    private: 
      SceneManager* scene_manager; 
        private : 
   //   void initAssets(); 
    public : 
     void run() ; 
     UI();
    ~UI();
     void UILoadFont(); 
     void UIUnLoadFont();
     static void DrawFadingText(float time, int x, int y, int fontsize,const char* text); 
     static void updateCamera();
     static void resetCamera();
     static void ChangeCameraTarget(Vector2 newtarget); 
     static void ChangeCameraZoom(float newzoom);  
    static Font getFont();
};
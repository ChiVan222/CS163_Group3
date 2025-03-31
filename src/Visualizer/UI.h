#pragma once
#include <raylib.h> 
#include "Scene.h"
class UI 
{   public :
     static float time; 
     static Texture2D background;
     static constexpr int wWidth = 1280; 
     static constexpr int wHeight = 720; 
     static constexpr int mFPS = 60; 
     static  Vector2 mousePos;
     static float fontsize; 
     static  Camera2D camera;

    private: 
      SceneManager* scene_manager; 
      Font mFont;
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
     Font getFont();
};
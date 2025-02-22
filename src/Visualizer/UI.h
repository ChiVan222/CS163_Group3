#pragma once
#include <raylib.h> 
#include <math.h>
#include "Button.h"
class UI 
{   
    private: 
       typedef enum Scenes{  
          Welcome = 0, Menu, Settings, Singly, Trie, Graph, Heap
       } Scenes;
      Scenes cScene;  
      static constexpr int wWidth = 1280; 
      static constexpr int wHeight = 720; 
      static constexpr int mFPS = 60; 
      Font mFont; 
    private : 
   //   void initAssets(); 
    public : 
      
     void run() ; 
     void DrawNode();
     Scenes getScenes(); 
     UI();
   //   ~UI();
     void UILoadFont(); 
     void UIUnLoadFont();
     void DrawFadingText(float time, int x, int y, int fontsize,const char* text);
     Font getFont();
};

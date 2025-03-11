#pragma once
#include <raylib.h> 
#include "Animation.h"

class UI 
{   
    public: 
      typedef enum Scenes{  
          Welcome = 0, Menu, Settings, Singly, Trie, Graph, Heap
      } Scenes;
    private: 
      Scenes cScene;  
      static constexpr int wWidth = 1280; 
      static constexpr int wHeight = 720; 
      static constexpr int mFPS = 60; 
      Font mFont; 
      Ani_LinkedListTraversal a;
      SinglyLinkedList list;
      bool created; 
    private : 
   //   void initAssets(); 
    public : 
     void run() ; 
     Scenes getScenes(); 
     UI();
   //   ~UI();
     void UILoadFont(); 
     void UIUnLoadFont();
     void DrawFadingText(float time, int x, int y, int fontsize,const char* text);
     void TrieScene(); 
     void GraphScene();
     void HeapScene(); 
     void SinglyScene(); 
     Font getFont();
};

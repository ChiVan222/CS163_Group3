#pragma once

#include <raylib.h>
#include "raymath.h"
#include <fstream>
//#include <bits/stdc++.h>

const float NODE_RADIUS = 15;
const float CODE_SIZE = 15;
enum Scenes{  
    Welcome = 0, Menu, Singly,Graph,Trie,Heap,Setting
} ;
enum InputType 
{
    Insert = 0 , Remove, Update, Search, AddEdge, Randomize, DijkstraRun
};
enum animation 
{ 
    None, Searching, Inserting, Updating, Removing, EdgeDrawing,Inserting_2,Straightening, DijkstraRunning
};
enum animation_state{ 
    Backward  =-1,Pause, Forward,  Continue, FirstState, FinalState
};

enum display{
    myfont =0, theme
};


struct Theme {
    Color BACKGROUND;
    
    Color MENU_BUTTON;
    Color HOVER_MENU;
    
    Color BUTTON;
    Color HOVER_BUTTON;
    Color SEPERATOR;
    
    Color INFOR;
    Color HIGHLIGHT_TEXT;
    
    Color HIGHLIGHT_NODE_1;
    Color HIGHLIGHT_NODE_2;
    Color NODE;
    Color LINE;
    
    Color SIDEBAR;
    Color WEIGHT;
    bool isDarkMode = true;
    void change();
};

const int FPS = 60;
extern Theme THEME;
extern const Vector2 ORIGIN;
extern Font FONT;
extern Texture2D PLAY, PAUSE, REPLAY, BACK, DOUBLE_BACK, NEXT, DOUBLE_NEXT, SPEED_UP, SPEED_DOWN, BACK_PAGE;

float FloatLerp(float start, float end, float amount);
void initResource();
void drawPicture(const char* path, Rectangle desRec, float rotation=0.0f, Vector2 origin=ORIGIN, Color color=WHITE);
void drawPicture(Texture2D texture, Rectangle desRec, float rotation=0.0f, Vector2 origin=ORIGIN, Color color=WHITE);

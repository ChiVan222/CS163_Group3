#include "Utility.h"
#include "CommonUI.h"
Texture2D PLAY;
Texture2D PAUSE;
Texture2D REPLAY;
Texture2D NEXT;
Texture2D DOUBLE_NEXT;
Texture2D BACK;
Texture2D DOUBLE_BACK;
Texture2D SPEED_UP;
Texture2D SPEED_DOWN;
Texture2D BACK_PAGE;
Font FONT;
Theme THEME;

const Vector2 ORIGIN = {0.0f, 0.0f};


void initResource() 
{
    PLAY = LoadTexture("../assets/Images/Play.png");
    PAUSE = LoadTexture("../assets/Images/Pause.png");
    REPLAY = LoadTexture("../assets/Images/Replay.png");
    BACK = LoadTexture("../assets/Images/Chevron left.png");
    DOUBLE_BACK = LoadTexture("../assets/Images/Chevrons left.png");
    NEXT = LoadTexture("../assets/Images/Chevron right.png");
    DOUBLE_NEXT = LoadTexture("../assets/Images/Chevrons right.png");
    SPEED_UP = LoadTexture("../assets/Images/Chevron up.png");
    SPEED_DOWN = LoadTexture("../assets/Images/Chevron down.png");
    BACK_PAGE = LoadTexture("../assets/Images/BackPage.png");

    THEME.BACKGROUND = {229,247,255, 255};
    THEME.MENU_BUTTON = {255,255,255,255};
    THEME.HOVER_MENU = {197,252,245,255};
    THEME.BUTTON = {229,247,255, 255};
    THEME.HOVER_BUTTON = {125,215,255, 255};
    THEME.SEPERATOR = {3, 178, 255, 255};
    THEME.INFOR = {6, 155, 91, 255};
    THEME.HIGHLIGHT_TEXT = {157, 238, 238, 255};
    THEME.HIGHLIGHT_NODE_1 = {55,221,149,255};
    THEME.HIGHLIGHT_NODE_2 = Fade(BLUE,60);
    THEME.NODE = {249,208,208,255};
    THEME.LINE = {182,157,157, 255};
    THEME.SIDEBAR = {250, 254, 255, 255};
    THEME.WEIGHT = {6, 155, 91, 255};
    
    //FONT = LoadFont("./Font/Roboto-Regular.ttf");
    FONT = LoadFontEx("../Font/SF-Pro-Display-Regular.otf", 40, 0, 255);
    
}


void drawPicture(const char* path, Rectangle desRec, float rotation, Vector2 origin, Color color) {
    Texture2D texture = LoadTexture(path);
    if (texture.id == 0) return;
    Rectangle srcRect = {0.0f, 0.0f, (float)texture.width, (float)texture.height};
    DrawTexturePro(texture, srcRect, desRec, origin, rotation, color);
    UnloadTexture(texture);
}

void drawPicture(Texture2D texture, Rectangle desRec, float rotation, Vector2 origin, Color color) {
    if (texture.id == 0) return;
    Rectangle srcRect = {0.0f, 0.0f, (float)texture.width, (float)texture.height};
    DrawTexturePro(texture, srcRect, desRec, origin, rotation, color);
}

float FloatLerp(float start, float end, float amount) {
    return start + amount * (end - start);
}


#include "Button.h"
Button::Button(const char* imgpath, Vector2 pos, float scale):position(pos){
     Image img =  LoadImage(imgpath); 
     int oWidth =img.width;
     int oHeight = img.height;   
     int nWidth = static_cast<int>(oWidth*scale);
     int nHeight = static_cast<int>(oHeight*scale);
     ImageResize(&img,nWidth,nHeight);
     texture =  LoadTextureFromImage(img);
     UnloadImage(img);

}
Button::~Button(){ 
    UnloadTexture(texture); 
}
void Button::Draw( )
{ 
    if(isHovered == None)
    {
        DrawTextureV(texture,position,GRAY);
    }else 
    {
        DrawTextureV(texture,position,WHITE);
    }
}
bool Button :: IsHovered(Vector2 mousePos)
{
    Rectangle rect =  {position.x,position.y, static_cast<float>(texture.width),static_cast<float>(texture.height)};
   if(CheckCollisionPointRec(mousePos,rect))
   {
     isHovered = HighLighting; 
     return true; 

   }
   return false; 
}

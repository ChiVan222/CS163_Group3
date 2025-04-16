#include "Animation.h"
#include <iostream>
#include "Scene.h"
#include <math.h>
//Animations Function
Animations::Animations(float duration) : isDone(false), elapsed_time(0), duration(duration) {}
void Animations::setDuration(float newduration)
{
     duration =newduration;
}

bool Animations::getState()
{
    return isDone;
}
void Animations::setState(bool state) 
{
    isDone = state;
}
//LinkedList Searching Function 
int Animations::getDuration()
{
    return duration;
}


void Ani_DrawEdge::updateAnimations(float deltaTime){
    if(isDone ||!target) return;
    elapsed_time+= deltaTime;
    
    Vector2 npos= Vector2(
     {std::min(dpos.x,cpos.x+(elapsed_time/duration)*(dpos.x-cpos.x)),
     std::min(dpos.y,cpos.y+(elapsed_time/duration)*(dpos.y- cpos.y))});

     int segments = 20;
     for (int i = 0; i < segments; i++) {
         float t1 = (float)i / segments;       
         float t2 = (float)(i + 1) / segments; 
         Vector2 p1 = Vector2({
             cpos.x + t1 * (npos.x - cpos.x),
             cpos.y + t1 * (npos.y - cpos.y)}
         );
         Vector2 p2 = Vector2({
             cpos.x + t2 * (npos.x - cpos.x),
             cpos.y + t2 * (npos.y - cpos.y)}
         );
          Color color = {
             (unsigned char)(128 * (1 - t1)), 
             0,                             
             (unsigned char)(128 + (127 * t1)), 
             255                             
         };
          DrawLineEx(p1, p2, target->getsize(), color);
     }



    // DrawLineEx(cpos,npos,target->getsize(),BLUE);
    if (elapsed_time >= duration) {
      isDone = true;
      elapsed_time = 0;
      Singly_Scene::ani = None; 
      target->isDraw = true; 
     }
 }
 void Ani_DrawEdge::play(){
    
     elapsed_time =0; 
     isDone =false;
 }
 void Ani_DrawEdge::updateTarget(Edge* egde)
 {  
     Singly_Scene::ani = EdgeDrawing;
     target = egde; 
      PolyNode* from = egde->getFrom();
       PolyNode* to = egde->getTo(); 
        float theta = atan2(to->getPosition().y - from->getPosition().y, 
                    to->getPosition().x - from->getPosition().x);

        cpos = Vector2({Singly_Scene::Node_radius * cos(theta) + from->getPosition().x,
                         Singly_Scene::Node_radius * sin(theta) + from->getPosition().y});

        dpos = Vector2({to->getPosition().x - Singly_Scene::Node_radius * cos(theta),
                         to->getPosition().y - Singly_Scene::Node_radius * sin(theta)});
       
     play();  
 }
 Ani_DrawEdge::Ani_DrawEdge(): Animations(0) ,target(nullptr)
 {
     isDone = true; 
 }

 Ani_Switch::Ani_Switch() : Animations(0) {
    isDone = true;
 }
 void Ani_Switch::play(){
    isDone = false;
        elapsed_time =0;
 }

void Ani_Switch::updateAnimations(float deltaTime){
   if (isDone) return;
    elapsed_time += deltaTime;
    float ratio = elapsed_time / duration;
    float t = ratio;
    if (t > 1.0f) t = 1.0f;
    if(Scene::isDarkMode) {
        t = t;
        std::cout << "On" <<"\n";
    }

    else {
        t = 1.0f-t;
        std::cout << "Off" <<"\n";
    }
    Vector2 newPos = Vector2({
        startPos.x + t * (targetPos.x - startPos.x),
        startPos.y + t * (targetPos.y - startPos.y)
    });
    std::cout << ratio <<"\n";
    Scene::modeSwitch.setCircle(newPos);
    if (ratio>=1.0f) {
        elapsed_time=0;
        isDone = true;
    }
}
    
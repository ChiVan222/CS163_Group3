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
//LinkedList Searching Function 
int Animations::getDuration()
{
    return duration;
}


void Ani_DrawEdge::updateAnimations(float deltaTime){
    if(isDone ||!target) return;
    elapsed_time+= deltaTime;
    Vector2 nposition= Vector2(
     {std::min(target->getTo()->getPosition().x,target->getFrom()->getPosition().x+(elapsed_time/duration)*target->getTo()->getPosition().x) -Singly_Scene::Node_radius,
     std::min(target->getTo()->getPosition().y,target->getFrom()->getPosition().y+(elapsed_time/duration)*target->getTo()->getPosition().y)});
   
   
    Vector2 from = Vector2({target->getFrom()->getPosition().x + Singly_Scene::Node_radius,target->getFrom()->getPosition().y});
    DrawLineBezier(from,nposition, target->getsize(),WHITE); 
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
    
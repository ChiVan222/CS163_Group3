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


// //Trie Insert
// Ani_TrieInsert::Ani_TrieInsert() : Animations(0), node_insert(nullptr), inserted(false), radius(20) {
//     isDone = true;
// }

// Ani_TrieInsert::Ani_TrieInsert(float duration) : Animations(duration), node_insert(nullptr), inserted(false), radius(20) {}


// void Ani_TrieInsert::updateTarget(Vector2 targetPos, float radius, TrieNodePrimary* node) {
//     this->targetPos = targetPos;
//     this->radius = radius;
//     this->node_insert = node;
//     startPos = Vector2({100, 100});  

//     play(); 
// }

// // Khởi động animation
// void Ani_TrieInsert::play() {
//     elapsed_time = 0;
//     isDone = false;
//     inserted = false;
// }

// // Cập nhật vị trí node mỗi frame
// void Ani_TrieInsert::updateAnimations(float deltaTime) {
//     if (isDone || !node_insert) return;

//     elapsed_time += deltaTime;
//     float t = elapsed_time / duration;
//     if (t > 1.0f) t = 1.0f;
//     std::cout << t<< "\n";
//     Vector2 newPos = Vector2({
//         startPos.x + t * (targetPos.x - startPos.x),
//         startPos.y + t * (targetPos.y - startPos.y)
//     });

//     node_insert->SetPosition(newPos);
//     if (t >=1.0f) {
//         isDone = true;
//         inserted = true;
//         Trie_Scene::ani = None;
//     }
// }

// bool Ani_TrieInsert::isInserted() const {
//     return inserted;
// }
// void Ani_TrieInsert::setDuration(float nduration){
//     duration = nduration;
// }

// TrieNodePrimary* Ani_TrieInsert::getNode() const {
//     return node_insert;
// }


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
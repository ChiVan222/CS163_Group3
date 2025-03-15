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
Ani_LinkedListSearching::Ani_LinkedListSearching(float duration, int target)
    : Animations(duration),  target(target){
        isDone =true;
}

Ani_LinkedListSearching::Ani_LinkedListSearching() : Animations(0){
    isDone =true;

}

void Ani_LinkedListSearching::updateAnimations(float deltaTime) {
    if(isDone||!Singly_Scene::cur||Singly_Scene::ani != Searching) return; 
    elapsed_time += deltaTime;
    Singly_Scene::cur->SetPrimaryHighLight();
    std::cout<<duration/Singly_Scene::Nodes.get_size();
    if (elapsed_time >= duration/Singly_Scene::Nodes.get_size()) {
        if (Singly_Scene::cur && Singly_Scene::cur->value != target) {
            Singly_Scene::cur->SetNullHighLight();
            Singly_Scene::cur = Singly_Scene::cur->next;
        } else if( Singly_Scene::cur && Singly_Scene::cur->value == target)
        {
            isDone = true;
            Singly_Scene::ani=None;
        }
         if(Singly_Scene::cur == nullptr)
        {
            isDone = true;
            Singly_Scene::ani=None;
            Singly_Scene::cur =Singly_Scene::Nodes.get_root();
        }
        
        elapsed_time = 0;
    }
}

void Ani_LinkedListSearching::updateTarget(int x)
{
  target = x; 
  Singly_Scene::ani  =Searching;
  if(!Singly_Scene::cur)
  {
    Singly_Scene::ani = None;
    return; 
  }
  Singly_Scene::cur->SetNullHighLight();
  Singly_Scene::cur = Singly_Scene::Nodes.get_root(); 
  play();
}

void Ani_LinkedListSearching::play() {
    elapsed_time = 0;
    isDone = false;
}

Ani_LinkedListSearching& Ani_LinkedListSearching::operator=(Ani_LinkedListSearching&& other) noexcept {
    if (this == &other) return *this;
    isDone= other.isDone;
    target = other.target; 
    return *this;
}


//Linked List Inserting 
Ani_LinkedListInsert::Ani_LinkedListInsert() : Animations(0){

}
Ani_LinkedListInsert::Ani_LinkedListInsert(float duration, int target, int radius, Vector2 position):Animations(duration), target(target), radius(radius),position(position)
{
     src_pos = Vector2({100,100});
     node_insert= nullptr;
     isDone = true; 
}
void Ani_LinkedListInsert::updateTarget(int x, int nradius, Vector2 nposition)
{
    if(isDone)
    {
        target = x; 
        radius = nradius;
        position = nposition; 
        Singly_Scene::ani = Inserting; 
        play(); 
    }
}
void Ani_LinkedListInsert::play()
{ 
    node_insert = new SinglyNode(src_pos, radius,target);
    if(Singly_Scene::cur) 
    {
      Singly_Scene::de.setDuration(0.5);
      Singly_Scene::Edges.push_back(new Edge(Singly_Scene::cur,node_insert));
      Singly_Scene::addFunction(2, std::bind(&Ani_DrawEdge::updateTarget, &Singly_Scene::de,Singly_Scene::Edges.back()));
    }
    Singly_Scene::Nodes.Insert(node_insert,duration/5);  
    Singly_Scene::cur = node_insert; 
    isDone =false;
}
void Ani_LinkedListInsert::updateAnimations(float deltaTime)
{ 
    
    if(isDone||!node_insert||Singly_Scene::ani != Inserting) return;
    std::cout<<elapsed_time<<"\n";
    elapsed_time += deltaTime;
    node_insert->SetPosition(Vector2({std::min(position.x,(elapsed_time/duration)*position.x),std::min(position.y,(elapsed_time/duration)*position.y)}));
    if (elapsed_time >= duration) {
        isDone = true;
        elapsed_time = 0;
        Singly_Scene::ani = None; 
    }
}

//Linked List Move
void Ani_MoveList::updateTarget(Vector2 newoffset, SinglyNode* node)
{
    offset=  newoffset; 
    root = node; 
    play();
}
Ani_MoveList::Ani_MoveList(float duration, Vector2 offset):Animations(duration),offset(offset),root(nullptr)
{ }
void Ani_MoveList::play()
{ 
    elapsed_time =0; 
    isDone =false;
}
Ani_MoveList::Ani_MoveList():Animations(0),offset(Vector2({0,0}))
{
   isDone =true;
}

void Ani_MoveList::updateAnimations(float deltaTime)
{
    if(isDone)return; 
    SinglyNode* cur = root; 
    elapsed_time += deltaTime; 
    if(elapsed_time<= duration ||!isDone)
   {
     while(cur)
        {
         Vector2 newpos  =  Vector2({cur->getPosition().x + offset.x*deltaTime/duration,cur->getPosition().y + offset.y*deltaTime/duration});
         cur->SetPosition(newpos); 
         cur = cur->next;
        }
        if(elapsed_time> duration)
        {
            isDone =true; 
            root= nullptr; 
            elapsed_time =0; 
        }
   }
}



Ani_LinkedListDelete::Ani_LinkedListDelete(float duration, int target):Animations(duration), target(target)
{
     isDone = true; 
}
Ani_LinkedListDelete::Ani_LinkedListDelete():Animations(0), target(0)
{
     isDone = true; 
}
void Ani_LinkedListDelete::updateTarget(int x)
{
    if(isDone)
    {
        Singly_Scene::ani = Removing; 
        target = x;
        Singly_Scene::cur = Singly_Scene::Nodes.get_root(); 
        play(); 
    }
}
#include <algorithm>
void Ani_LinkedListDelete::play() {
    if(Singly_Scene::Nodes.get_root()->value == target) 
    {
        SinglyNode* tmp =Singly_Scene::Nodes.get_root(); 
        Singly_Scene::Nodes.set_root(Singly_Scene::Nodes.get_root()->next); 
        Singly_Scene::cur = Singly_Scene::Nodes.get_root(); 
        Singly_Scene::Edges.erase(
            std::remove_if(Singly_Scene::Edges.begin(),Singly_Scene::Edges.end(),[tmp](Edge* edge){
                    if (edge->getFrom() == tmp || edge->getTo() == tmp) {
                        delete edge; 
                        return true;
                    }
                    return false;
                }),
        Singly_Scene::Edges.end());
        if(tmp->next)
        {
            Singly_Scene::m.setDuration(duration);
            Singly_Scene::m.updateTarget(Vector2({(float)(-Singly_Scene::Node_radius*2-50),0}),tmp->next);
        }
        Singly_Scene::Nodes.size--; 
        Singly_Scene::ani =None;
        delete tmp;
        return; 
    }
    elapsed_time = 0;
    isDone = false; 
}
void Ani_LinkedListDelete::updateAnimations(float deltaTime)
{
    if(isDone||Singly_Scene::ani != Removing) return;
    elapsed_time += deltaTime;
    if(Singly_Scene::cur)Singly_Scene::cur->SetPrimaryHighLight();
    if (elapsed_time >= duration/Singly_Scene::Nodes.get_size()) {
        if (Singly_Scene::cur && Singly_Scene::cur->next&& Singly_Scene::cur->next->value != target) {
            Singly_Scene::cur->SetNullHighLight();
            Singly_Scene::cur = Singly_Scene::cur->next;
        } else
        {
            Singly_Scene::Nodes.DeleteNode(Singly_Scene::cur,duration); 
            isDone = true;
            Singly_Scene::cur = Singly_Scene::Nodes.get_root();
            Singly_Scene::ani=None;
        }
        elapsed_time = 0;
    }
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
Ani_DrawEdge::Ani_DrawEdge(float duration): Animations(duration) ,target(nullptr)
{
    isDone = true; 
}
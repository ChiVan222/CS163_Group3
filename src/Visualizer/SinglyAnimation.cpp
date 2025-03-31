#include "SinglyAnimation.h"
#include <iostream>
#include "Scene.h"
#include <math.h>
#include <raymath.h>
#include "UI.h"
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
      Singly_Scene::addFunction(Singly_Scene::animation_queue,2, std::bind(&Ani_DrawEdge::updateTarget, &Singly_Scene::de,Singly_Scene::Edges.back()));
    }
    Singly_Scene::Nodes.Insert(node_insert,duration/5);  
    Singly_Scene::cur = node_insert; 
    isDone =false;
}
void Ani_LinkedListInsert::updateAnimations(float deltaTime)
{ 
    
    if(isDone||!node_insert||Singly_Scene::ani != Inserting) return;
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
            Singly_Scene::ani=None;
        }
        elapsed_time = 0;
    }
}

Ani_InsertRandomList::Ani_InsertRandomList(float duration): Animations(duration) ,target(nullptr)
{
    isDone = true; 
}
void Ani_InsertRandomList::play()
{ 
    isDone = false;
    elapsed_time=0;  
    Singly_Scene::cur = Singly_Scene::Nodes.get_root();
}

void Ani_InsertRandomList::updateTarget(SinglyNode* node){
    if(!Singly_Scene::Nodes.get_root())
    { 
         Singly_Scene::Nodes.set_root(node); 
         Singly_Scene::cur = node; 
         UI::camera.target  =  node->getPosition();
         return; 
    }
    Singly_Scene::ani = Inserting_2; 
    startpos = Singly_Scene::Nodes.get_root()->getPosition();
    target = node;
    play(); 
}
void Ani_InsertRandomList::updateAnimations(float deltaTime)
{ 
    if(isDone||!target||Singly_Scene::ani != Inserting_2) return;
    
    target->Draw(); 
    elapsed_time += deltaTime;
    float t = elapsed_time / duration;
    Vector2 position = target->getPosition(); 
    Vector2 newPos = { startpos.x + t * (position.x - startpos.x),
                       startpos.y + t * (position.y - startpos.y) };
    Singly_Scene::Nodes.get_root()->SetPosition(newPos);
    Singly_Scene::addFunction(Singly_Scene::UI_animation_queue,2, [newPos]() {
        UI::ChangeCameraTarget(newPos); 
    });
    float newzoom = 1; 
    Singly_Scene::addFunction(Singly_Scene::UI_animation_queue,2,[newzoom]() {
        UI::ChangeCameraZoom(newzoom); 
    });
    Singly_Scene::Nodes.get_root()->ForwardDistanceConstraints(2*Singly_Scene::Node_radius +50);
    // Singly_Scene::Nodes.get_root()->ForwardAngleConstraints(2*PI/3);
    if(CheckCollisionCircles(Singly_Scene::Nodes.get_root()->getPosition(),Singly_Scene::Node_radius,target->getPosition(),Singly_Scene::Node_radius))
    {
        Singly_Scene::Nodes.InsertAtEnd(target,2*Singly_Scene::Node_radius +50);
        isDone = true;
        elapsed_time = 0;
        Singly_Scene::Nodes.get_root()->ForwardDistanceConstraints(2*Singly_Scene::Node_radius +50);
        // Singly_Scene::Nodes.get_root()->ForwardAngleConstraints(2*PI/3);

        Singly_Scene::ani = None; 
    }
    if (elapsed_time >= duration) {
        isDone = true;
        elapsed_time = 0;
        Singly_Scene::ani = None; 
    }
}
Ani_MoveNode::Ani_MoveNode(float duration):Animations(duration)
{
    isDone = true; 
}
void Ani_MoveNode::play()
{ 
    isDone = false;
    elapsed_time=0;  
    Singly_Scene::cur = target;
     
}
Ani_Straighten::Ani_Straighten(float duration): Animations(duration) 
{
    isDone = true; 
}
void Ani_MoveNode::updateTarget(SinglyNode* node,Vector2 Endpos){
    if(!node)
    { 
         return; 
    }
    startpos = node->getPosition();
    endpos = Endpos;
    target = node;
    play(); 
}
void Ani_MoveNode::updateAnimations(float deltaTime)
{
    if(isDone||!target)return; 
    elapsed_time += deltaTime; 
    if(elapsed_time<= duration ||!isDone)
   {
        float t = elapsed_time / duration;
        Vector2 newPos = { startpos.x + t * (endpos.x - startpos.x),
                       startpos.y + t * (endpos.y - startpos.y) };
        target->SetPosition(newPos); 
        if(target == Singly_Scene::Nodes.get_root())
        {
            UI::camera.target = Vector2Lerp(UI::camera.target, newPos, 0.3);
            UI::camera.zoom =1; 
        }
        target->ForwardDistanceConstraints(2*Singly_Scene::Node_radius+50);
        // target->ForwardAngleConstraints(2*PI/3);

        if(elapsed_time> duration)
        {
            isDone =true; 
            elapsed_time =0; 
        }
   }
}

void Ani_Straighten::play()
{ 
    isDone = false;
    elapsed_time=0;  
    Singly_Scene::mn.setDuration(1); 
    Singly_Scene::mn.updateTarget(Singly_Scene::Nodes.get_root(), endpos);  
}
void Ani_Straighten ::updateTarget(Vector2 Endpos)
{ 
    endpos = Endpos;
    Singly_Scene:: ani = Straightening; 
    play(); 
}
void Ani_Straighten::updateAnimations(float deltaTime)
{
    if(isDone)return; 
    elapsed_time += deltaTime; 
    if(elapsed_time>= Singly_Scene::mn.getDuration()&& Singly_Scene::mn.getState())
   {
       if(Singly_Scene::cur->next)
       { 
        Singly_Scene::mn.setDuration(0.2); 
        Vector2 npos  =  Vector2{Singly_Scene::cur->getPosition().x + 2*Singly_Scene::Node_radius+50, Singly_Scene::cur->getPosition().y};
        Singly_Scene::mn.updateTarget(Singly_Scene::cur->next,npos);  
       }
       else
        {
            isDone =true; 
            elapsed_time =0; 
            Singly_Scene::ani = None;
        }
   }
}
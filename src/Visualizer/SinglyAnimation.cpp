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
    if(isDone||!Singly_Scene::cur) return; 
    elapsed_time += fabs(deltaTime);
    Singly_Scene::cur->SetPrimaryHighLight();
    if (elapsed_time >= duration/Singly_Scene::Nodes.get_size()) {

            if (Singly_Scene::cur && (Singly_Scene::cur->value != target || Singly_Scene::ani_state == Backward)) {
                Singly_Scene::cur->SetNullHighLight();
                std::cout<<Singly_Scene::cur->value<<"\n";
                if(Singly_Scene::ani_state == Forward)Singly_Scene::cur = Singly_Scene::cur->next;
                else if(Singly_Scene::ani_state == Backward)
                {
                    if(Singly_Scene::cur != Singly_Scene::Nodes.get_root())
                    { 
                        SinglyNode* tmp = Singly_Scene::Nodes.get_root();
                        while(tmp&& tmp->next != Singly_Scene::cur)
                        {
                         tmp = tmp->next; 
                        }
                        Singly_Scene::cur = tmp;
                    }
                }
            } else if( Singly_Scene::cur && Singly_Scene::cur->value == target && Singly_Scene::ani_state == Forward)
            {
                isDone = true;
                Singly_Scene::ani=None;
                Singly_Scene::ani_his.push(Singly_Scene::cur_animation);
            }
            else if( Singly_Scene::cur && Singly_Scene::cur== Singly_Scene::Nodes.get_root() && Singly_Scene::ani_state == Backward)
            {
                isDone = true;
                Singly_Scene::ani=None;
                Singly_Scene::ani_replay_his.push(Singly_Scene::cur_animation);
            }
             if(Singly_Scene::cur == nullptr)
            {
                isDone = true;
                Singly_Scene::ani=None;
                Singly_Scene::cur =Singly_Scene::Nodes.get_root();
                if(Singly_Scene::ani_state == Forward) Singly_Scene::ani_his.push(Singly_Scene::cur_animation);
                else if(Singly_Scene::ani_state == Backward )Singly_Scene::ani_replay_his.push(Singly_Scene::cur_animation);
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
  if(Singly_Scene::ani_state==Forward) Singly_Scene::cur = Singly_Scene::Nodes.get_root();
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
    elapsed_time = other.elapsed_time; 
    return *this;
}

Ani_LinkedListSearching& Ani_LinkedListSearching::operator=(const Ani_LinkedListSearching& other) noexcept {
    if (this == &other) return *this;
    isDone= other.isDone;
    target = other.target; 
    elapsed_time = other.elapsed_time ;
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
            if(Singly_Scene::ani_state == Forward) 
            {
                Singly_Scene::Edges.push_back(new Edge(Singly_Scene::cur,node_insert));
                Singly_Scene::addFunction(Singly_Scene::animation_queue,Singly_Scene::cur_animation.first-2, std::bind(&Ani_DrawEdge::updateTarget, &Singly_Scene::de,Singly_Scene::Edges.back()));

            }
        }
        if(Singly_Scene::ani_state == Forward) 
        {
            Singly_Scene::Nodes.Insert(node_insert,duration/5);       
             Singly_Scene::cur = node_insert; 
        }

        if(Singly_Scene::ani_state == Backward) 
        {
            SinglyNode* cur   = Singly_Scene::Nodes.get_root(); 
            while(cur && cur->next && cur->next->getValue() != node_insert->getValue())
            {
                cur = cur->next;   
            }
            Singly_Scene::Nodes.DeleteNode(cur,duration/5); 
            Singly_Scene::ani = None;
            Singly_Scene::ani_replay_his.push(Singly_Scene::cur_animation);
            return; 
        }
    isDone =false;
}
void Ani_LinkedListInsert::updateAnimations(float deltaTime)
{ 
    
    if(isDone||!node_insert) return;
    if(elapsed_time < 0 && deltaTime < 0 )return; 
    elapsed_time += deltaTime;
    if(elapsed_time <=0)
    { 
        isDone = true;
        elapsed_time = 0;
        Singly_Scene::ani = None; 
        Singly_Scene::ani_replay_his.push(Singly_Scene::cur_animation);
    }
    node_insert->SetPosition(Vector2({std::min(position.x,(elapsed_time/duration)*position.x),std::min(position.y,(elapsed_time/duration)*position.y)}));
    if (elapsed_time >= duration) {
        isDone = true;
        elapsed_time = 0;
        Singly_Scene::ani = None;
        Singly_Scene::ani_his.push(Singly_Scene::cur_animation);
    }
}
Ani_LinkedListInsert& Ani_LinkedListInsert::operator=(const Ani_LinkedListInsert& other) noexcept {
    if (this == &other) return *this;
    isDone= other.isDone;
    target = other.target; 
    elapsed_time = other.elapsed_time ;
    radius  = other.radius;
    position = other.position;
    node_insert = other.node_insert; 
    src_pos = other.src_pos;
    return *this;
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

    if(elapsed_time < 0 && deltaTime < 0 )return; 
    elapsed_time += deltaTime;
    if(elapsed_time <=0)
    { 
        isDone = true;
        elapsed_time = 0;
        Singly_Scene::ani = None; 
        Singly_Scene::ani_replay_his.push(Singly_Scene::cur_animation);
    }

    if(elapsed_time<= duration ||!isDone)
   {

         Vector2 newpos  =  Vector2({cur->getPosition().x + offset.x*deltaTime/duration,cur->getPosition().y + offset.y*deltaTime/duration});
         cur->SetPosition(newpos); 
        cur->BackwardDistanceConstraints(2*Singly_Scene::Node_radius +50);
        if(elapsed_time> duration)
        {
            isDone =true; 
            root= nullptr; 
            elapsed_time =0; 
            Singly_Scene::ani_his.push(Singly_Scene::cur_animation);
        }
   }
}

Ani_MoveList& Ani_MoveList::operator=(const Ani_MoveList& other) noexcept {
    if (this == &other) return *this;
    isDone= other.isDone;
    root = other.root; 
    offset =    other.offset;
    elapsed_time = other.elapsed_time ;
    return *this;
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
    if(isDone) return;
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
Ani_LinkedListDelete& Ani_LinkedListDelete::operator=(const Ani_LinkedListDelete& other) noexcept {
    if (this == &other) return *this;
    isDone= other.isDone;

    elapsed_time = other.elapsed_time ;
    return *this;
}
Ani_InsertRandomList::Ani_InsertRandomList(float duration): Animations(duration) ,target(nullptr)
{
    isDone = true; 
}
Ani_InsertRandomList::Ani_InsertRandomList(): Animations(0) ,target(nullptr)
{
    isDone = true; 
}
void Ani_InsertRandomList::play()
{ 
    isDone = false;
  if( Singly_Scene::ani_state == Forward)
  {
    elapsed_time=0;  
  }else if (Singly_Scene::ani_state == Backward){
    // elapsed_time = (1- target->getRadius()/(Vector2Length(target->getPosition()-startpos)) - 0.1)*duration; 
    elapsed_time = duration;
  }
    Singly_Scene::cur = Singly_Scene::Nodes.get_root();
}

void Ani_InsertRandomList::updateTarget(Vector2 position, int value){
    if(!Singly_Scene::Nodes.get_root())
    { 
         target = new SinglyNode(position, Singly_Scene::Node_radius, value); 
         Singly_Scene::Nodes.set_root(target); 
         Singly_Scene::cur = target; 
         UI::camera.target  =  target->getPosition();
         return; 
    }
    Singly_Scene::ani = Inserting_2; 
    startpos = Singly_Scene::Nodes.get_root()->getPosition();
    target = new SinglyNode(position, Singly_Scene::Node_radius, value); 
    play(); 
}
void Ani_InsertRandomList::updateAnimations(float deltaTime)
{ 
    if(isDone||!target) return;
    target->Draw(); 
    if(elapsed_time < 0 && deltaTime<0 ) return; 
    elapsed_time += deltaTime;
    if(elapsed_time <= 0 && Singly_Scene::ani_state == Backward)
    { 
        Singly_Scene::Nodes.DeleteAtEnd(); 
        delete target;    
        target =nullptr; 
        isDone = true;  
        Singly_Scene::ani = None;
        Singly_Scene::ani_replay_his.push(Singly_Scene::cur_animation); 
        return; 
    } 
    float t = elapsed_time / duration;
    Vector2 position = target->getPosition(); 
    Vector2 newPos = { startpos.x + t * (position.x - startpos.x),
                       startpos.y + t * (position.y - startpos.y) };
    Singly_Scene::Nodes.get_root()->SetPosition(newPos);
    UI::ChangeCameraTarget(newPos);
    float newzoom = 1; 
    UI::ChangeCameraZoom(newzoom);
    Singly_Scene::Nodes.get_root()->ForwardDistanceConstraints(2*Singly_Scene::Node_radius +50);
    // Singly_Scene::Nodes.get_root()->ForwardAngleConstraints(2*PI/3);
    if(Singly_Scene::ani_state == Forward && CheckCollisionCircles(Singly_Scene::Nodes.get_root()->getPosition(),Singly_Scene::Node_radius,target->getPosition(),Singly_Scene::Node_radius))
    {
        Singly_Scene::Nodes.InsertAtEnd(target,2*Singly_Scene::Node_radius +50);
        isDone = true;
        elapsed_time = 0;
        Singly_Scene::ani_his.push(Singly_Scene::cur_animation); 
        Singly_Scene::Nodes.get_root()->ForwardDistanceConstraints(2*Singly_Scene::Node_radius +50);
        // Singly_Scene::Nodes.get_root()->ForwardAngleConstraints(2*PI/3);
        Singly_Scene::ani = None;   
    }
    if (elapsed_time >= duration) {
        Singly_Scene::cur_animation.first++; 
        Singly_Scene::ani_his.push(Singly_Scene::cur_animation); 
        isDone = true;
        elapsed_time = 0;
        Singly_Scene::ani = None; 
    }
}


Ani_InsertRandomList& Ani_InsertRandomList::operator=(const Ani_InsertRandomList& other) noexcept {
    if (this == &other) return *this;
    isDone= other.isDone;
    root = other.root; 
    endpos = other.endpos; 
    startpos = other.startpos;
    elapsed_time = other.elapsed_time ;
    return *this;
}

Ani_MoveNode::Ani_MoveNode(float duration):Animations(duration)
{
    isDone = true; 
}
Ani_MoveNode::Ani_MoveNode():Animations(0)
{
    isDone = true; 
}
void Ani_MoveNode::play()
{ 
    isDone = false;
    if( Singly_Scene::ani_state == Forward)
    {
      elapsed_time=0;  
    }else if (Singly_Scene::ani_state == Backward){
      elapsed_time = duration;
    }
    Singly_Scene::cur = target;
     
}
Ani_Straighten::Ani_Straighten(float duration): Animations(duration) 
{
    isDone = true; 
}
Ani_Straighten::Ani_Straighten(): Animations(0) 
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
    if(elapsed_time < 0 && deltaTime < 0 )return; 
    elapsed_time += deltaTime; 
    if(elapsed_time <= 0 && Singly_Scene::ani_state == Backward)
    { 
        isDone = true;  
        Singly_Scene::ani = None;
        Singly_Scene::ani_replay_his.push(Singly_Scene::cur_animation); 
        return; 
    }  
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
            Singly_Scene::ani_his.push(Singly_Scene::cur_animation);
        }
   }
}

Ani_MoveNode& Ani_MoveNode::operator=(const Ani_MoveNode& other) noexcept {
    if (this == &other) return *this;
    isDone= other.isDone;
    endpos = other.endpos; 
    startpos = other.startpos;
    elapsed_time = other.elapsed_time ;
    return *this;
}
void Ani_Straighten::play()
{ 
    isDone = false;
    if( Singly_Scene::ani_state == Forward)
    {
      elapsed_time=0;  
    }else if (Singly_Scene::ani_state == Backward){
      elapsed_time = duration;
    }
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
    if(elapsed_time < 0 && deltaTime < 0 )return; 
    elapsed_time += deltaTime; 
    if(elapsed_time <= 0 && Singly_Scene::ani_state == Backward)
    { 
        isDone = true;  
        Singly_Scene::ani = None;
        Singly_Scene::ani_replay_his.push(Singly_Scene::cur_animation); 
        return; 
    } 
    if(Singly_Scene::ani_state == Forward && elapsed_time>= Singly_Scene::mn.getDuration()&& Singly_Scene::mn.getState())
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
            Singly_Scene::ani_his.push(Singly_Scene::cur_animation);
        }
   }
}
Ani_Straighten& Ani_Straighten::operator=(const Ani_Straighten& other) noexcept {
    if (this == &other) return *this;
    isDone= other.isDone;
    endpos = other.endpos; 
    elapsed_time = other.elapsed_time ;
    return *this;
}
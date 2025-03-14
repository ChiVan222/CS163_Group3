#include "Animation.h"
#include <iostream>
#include "Scene.h"
Animations::Animations(float duration) : isDone(false), elapsed_time(0), duration(duration) {}

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
        } else {
            if(Singly_Scene::cur == nullptr)Singly_Scene::cur =Singly_Scene::Nodes.get_root();
            isDone = true;
            Singly_Scene::ani=None;
        }
        elapsed_time = 0;
    }
}
void Ani_LinkedListSearching::updateTarget(int x)
{
  target = x; 
  Singly_Scene::cur->SetNullHighLight();
  Singly_Scene::cur = Singly_Scene::Nodes.get_root(); 
  play();
}
void Ani_LinkedListSearching::play() {
    elapsed_time = 0;
    isDone = false;
    index =0 ; 
}

Ani_LinkedListSearching& Ani_LinkedListSearching::operator=(Ani_LinkedListSearching&& other) noexcept {
    if (this == &other) return *this;
    isDone= other.isDone;
    target = other.target; 
    return *this;
}

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
        play(); 
    }
}
void Ani_LinkedListInsert::play()
{ 
    node_insert = new SinglyNode(src_pos, radius,target);
    if(Singly_Scene::cur) Singly_Scene::Edges.push_back(new Edge(Singly_Scene::cur,node_insert));
    Singly_Scene::Nodes.Insert(node_insert,duration/5);  
    Singly_Scene::cur = node_insert; 
    isDone =false;
}
#include <math.h>
void Ani_LinkedListInsert::updateAnimations(float deltaTime)
{ 
    if(isDone||!node_insert||Singly_Scene::ani != Inserting) return;
    elapsed_time += deltaTime;
    node_insert->SetPosition(Vector2({(elapsed_time/duration)*position.x,(elapsed_time/duration)*position.y}));
    if (elapsed_time >= duration) {
        isDone = true;
        elapsed_time = 0;
        Singly_Scene::ani = None; 
        node_insert->SetPosition(Vector2({(float)std::floor(node_insert->getPosition().x) ,(float)std::floor( node_insert->getPosition().y)}));
    }
}
bool Animations::getState()
{
    return isDone;
}
void Ani_MoveList::updateTarget(Vector2 newoffset, SinglyNode* node)
{
    offset=  newoffset; 
    std::cout<<offset.x<<" "<<offset.y <<'\n';
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

void Animations::setDuration(float newduration)
{
     duration =newduration;
}
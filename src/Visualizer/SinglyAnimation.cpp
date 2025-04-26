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
Color MultiplyColor(Color color, float factor) {
    Color result;
    result.r = color.r * factor;
    result.g = color.g * factor;
    result.b = color.b * factor;
    result.a = color.a;  
    return result;
}
Color MultiplyTransparency(Color color, float factor) {
    Color result;
    result.r = color.r;
    result.g = color.g;
    result.b = color.b;
    result.a = color.a*factor;  
    return result;
}
void Ani_LinkedListSearching::updateAnimations(float deltaTime) {
    if(isDone||!Singly_Scene::cur) return; 
    if (isDone || history.empty() || !isPrerunDone) return;

    switch (Singly_Scene::ani_state) {
        case animation_state::Pause:
            break;

        case animation_state::Backward:

            if (currentStep > 0) {
                const auto& snap = history[currentStep];
                Edge* edge= snap.edge;
                SinglyNode* cur = snap.cur; 
                if(cur) cur->SetNullHighLight();
                if(edge)
                {   
                    edge->setColor(WHITE); 
                }
                Singly_Scene::cur  = snap.cur;
                currentStep--;
            }
           Singly_Scene::ani_state = animation_state::Pause;
            break;

        case animation_state::Forward:
            if (currentStep + 1 < history.size()) 
            {
                const auto& snap = history[currentStep];
                Edge* edge= snap.edge;
                SinglyNode* cur = snap.cur; 
                if(cur) cur->SetNullHighLight();
                if(edge)
                {   
                    edge->setColor(WHITE); 
                }
                currentStep++;
            }
            Singly_Scene::ani_state = animation_state::Pause;
            break;

        case animation_state::Continue:
            break;
        default:
            break;         
    }

    if (Singly_Scene::ani_state != animation_state::Pause) elapsed_time += deltaTime;
    const auto& snap = history[currentStep];
    Edge* edge= snap.edge;
    
    if(edge)
    {   
        // edge->setColor(MultiplyTransparency(PURPLE,0.2 + elapsed_time/duration));
        PolyNode* from = edge->getFrom();
        PolyNode* to = edge->getTo(); 
         float theta = atan2(to->getPosition().y - from->getPosition().y, 
                     to->getPosition().x - from->getPosition().x);
 
         Vector2 cpos = Vector2({Singly_Scene::Node_radius * cos(theta) + from->getPosition().x,
                          Singly_Scene::Node_radius * sin(theta) + from->getPosition().y});
 
         Vector2 dpos = Vector2({to->getPosition().x - Singly_Scene::Node_radius * cos(theta),
                          to->getPosition().y - Singly_Scene::Node_radius * sin(theta)});
        Vector2 npos= Vector2(
            {std::min(dpos.x,cpos.x+(elapsed_time/(duration/history.size()))*(dpos.x-cpos.x)),
            std::min(dpos.y,cpos.y+(elapsed_time/(duration/history.size()))*(dpos.y- cpos.y))});
       
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
                 DrawLineEx(p1, p2, edge->getsize(), color);
            } 
    }
   
   
    Singly_Scene::cur  = snap.cur;
    Singly_Scene::cur->SetPrimaryHighLight();
    if (elapsed_time >= duration/history.size()) {
            if (Singly_Scene::cur && Singly_Scene::cur->value != target) {
                Singly_Scene::cur->SetNullHighLight();
                Singly_Scene::cur = Singly_Scene::cur->next;
                if(edge)edge->setColor(WHITE);
    
                if (++currentStep >= history.size()) {
                    isDone = true;
                    Singly_Scene::ani = None;
                    return;
                }
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
void Ani_LinkedListSearching::prerun()
{
    history.clear();
    SinglyNode* ncur =  Singly_Scene::Nodes.get_root();  
    Edge* edge = nullptr;

    
    while(ncur && ncur->value != target)
    {
        auto it = std::find_if(Singly_Scene::Edges.begin(), Singly_Scene::Edges.end(),
        [ncur](Edge* edge) {
            return edge->getFrom() == ncur;
          });
        if(it != Singly_Scene::Edges.end())
        {
         edge = *it; 
        }else{
            edge =nullptr; 
        }

        history.push_back({ncur,edge});
        ncur = ncur->next; 
    }
    if(ncur && ncur->value == target)
    {
       history.push_back({ncur,nullptr});
    }else
    {
        history.push_back({Singly_Scene::Nodes.get_root(),nullptr}); 
    }
    currentStep =0;
    this->setDuration(0.5*history.size()); 
    isPrerunDone =true; 
}
void Ani_LinkedListSearching::updateTarget(int x)
{
  target = x; 
  Singly_Scene::ani  =Searching;
  if(!Singly_Scene::Nodes.get_root())
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
    prerun();
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
void Ani_LinkedListInsert::reset()
{
    cur = nullptr; 
    target= 0 ; 
    loaded = false; 
    isPrerunDone = false; 
    isDone  =true;  
    elapsed_time = 0 ; 
    history.clear(); 
}
void Ani_LinkedListInsert::play()
{ 
    
    node_insert = new SinglyNode(src_pos, radius,target);
    isDone =false;
    prerun(); 
}
void Ani_LinkedListInsert::updateAnimations(float deltaTime)
{ 
    
    if (isDone || history.empty() || !isPrerunDone||!node_insert ) return;
    switch (Singly_Scene::ani_state) {
        case animation_state::Pause:
            break;

        case animation_state::Backward:

            if (currentStep > 0) {
                currentStep--;
                loaded = false; 
            }
           Singly_Scene::ani_state = animation_state::Pause;
            break;

        case animation_state::Forward:
            if (currentStep + 1 < history.size()) 
            {
                currentStep++;
                loaded =false;  
            }
            Singly_Scene::ani_state = animation_state::Pause;
            break;

        case animation_state::Continue:
            break;
        default:
            break;         
    }
 
    if (Singly_Scene::ani_state != animation_state::Pause) elapsed_time += deltaTime;
    if(!loaded)
    {
        const auto& snapshot = history[currentStep];
        Singly_Scene::loadInfo(snapshot.info); 
        index = snapshot.index; 
        loaded = true; 
    }

    SinglyNode* ncur = Singly_Scene::Nodes.get_root(); 
    for(int i =0 ; i < index;i++)
    {
        ncur = ncur->next; 
    }
    if(Singly_Scene::cur == nullptr) ncur = nullptr; 
    if(ncur)ncur->SetPrimaryHighLight(); 
    if(ncur == Singly_Scene::cur && currentStep != history.size()-1 )
    {
        if(Singly_Scene::ani_state != Pause)
        {
            if(insertnode) insertnode->Draw();
            if(!inserted)
            {
                insertnode  = new SinglyNode(node_insert);

                if(ncur) 
                {
                    Singly_Scene::Edges.push_back(new Edge(Singly_Scene::cur,insertnode));
                    Singly_Scene::addFunction(Singly_Scene::animation_queue,Singly_Scene::cur_animation.first-2, std::bind(&Ani_DrawEdge::updateTarget, &Singly_Scene::de,Singly_Scene::Edges.back()));
                }
                Singly_Scene::Nodes.Insert(insertnode,(duration/history.size())/5);  
                // Singly_Scene::Nodes.InsertAfter(ncur,node_insert);
                inserted = true; 
            }
            insertnode->SetPosition(Vector2({std::min(position.x,(elapsed_time/(duration/history.size()))*position.x),std::min(position.y,(elapsed_time/(duration/history.size()))*position.y)}));
            if (elapsed_time >= duration/history.size()) {
                isDone  = true; 
                index= 0 ; 
                inserted=0 ; 
                Singly_Scene::ani = None; 
                loaded = 0; 
                isPrerunDone = 0 ;
                Singly_Scene::cur = insertnode; 
               elapsed_time =0 ;
                return; 
            }
        }
    }else if(currentStep == history.size()-1)
    {
        if (elapsed_time >= duration/history.size()) {
            isDone  = true; 
            index= 0 ; 
            inserted=0 ; 
            Singly_Scene::ani = None; 
            
            loaded = 0; 
            isPrerunDone = 0 ;
            elapsed_time =0 ;
            return;    
        }
    }else
    {
        Edge* edge; 
        auto it = std::find_if(Singly_Scene::Edges.begin(), Singly_Scene::Edges.end(),
        [ncur](Edge* edge) {
            return edge->getFrom() == ncur;
          });
        if(it != Singly_Scene::Edges.end())
        {
         edge = *it; 
        }else{
            edge =nullptr; 
        }
        if(edge)
        {   
            PolyNode* from = edge->getFrom();
            PolyNode* to = edge->getTo(); 
             float theta = atan2(to->getPosition().y - from->getPosition().y, 
                         to->getPosition().x - from->getPosition().x);
     
             Vector2 cpos = Vector2({Singly_Scene::Node_radius * cos(theta) + from->getPosition().x,
                              Singly_Scene::Node_radius * sin(theta) + from->getPosition().y});
     
             Vector2 dpos = Vector2({to->getPosition().x - Singly_Scene::Node_radius * cos(theta),
                              to->getPosition().y - Singly_Scene::Node_radius * sin(theta)});
            Vector2 npos= Vector2(
                {std::min(dpos.x,cpos.x+(elapsed_time/(duration/history.size()))*(dpos.x-cpos.x)),
                std::min(dpos.y,cpos.y+(elapsed_time/(duration/history.size()))*(dpos.y- cpos.y))});
           
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
                     DrawLineEx(p1, p2, edge->getsize(), color);
                } 
        }    
        if (elapsed_time >= duration/history.size()) {
               ncur->SetNullHighLight();
               ncur =ncur->next;
               if(edge)edge->setColor(WHITE);
               if (++currentStep >= history.size()) {
                    isDone = true;
                    Singly_Scene::ani = None;
                    return;
                }
                loaded = false; 
                elapsed_time = 0;
            } 
    }
}
void Ani_LinkedListInsert::prerun()
{
    history.clear();
    SinglyNode* ncur = Singly_Scene::Nodes.get_root();
    Edge* edge= nullptr; 
    int nindex= -1 ; 
    while(ncur&& ncur != Singly_Scene::cur)
    {
       
        history.push_back({++nindex,Singly_Scene::getInfo()});
        ncur = ncur->next; 
    }
    history.push_back({++nindex,Singly_Scene::getInfo()});
    SinglyNode* insert_n = new SinglyNode(node_insert); 
    insert_n->SetPosition(position); 
    if(ncur) 
    {
        Singly_Scene::Edges.push_back(new Edge(ncur,insert_n));
    }
    Singly_Scene::cur =insert_n;

    Singly_Scene::Nodes.InsertAfter(ncur,insert_n);
    history.push_back({++nindex,Singly_Scene::getInfo()});
    isPrerunDone = true;  
    currentStep = 0 ; 
    std::cout<<"Preruned"<<"\n";
    Singly_Scene::loadInfo(history[0].info);
    Singly_Scene::ani_state = Pause; 
    duration = 0.5*history.size(); 
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
    if(!Singly_Scene::Nodes.get_root())
    {
        return ;
    } 
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
   
    elapsed_time = 0;
    isDone = false; 
    prerun(); 
}
void Ani_LinkedListDelete::updateAnimations(float deltaTime)
{
    if (isDone || history.empty() || !isPrerunDone ) return;
    Singly_Scene::stepindex = currentStep;  
    switch (Singly_Scene::ani_state) {
        case animation_state::Pause:
            break;
        case animation_state::Backward:

            if (currentStep > 0) {
                currentStep--;
                loaded = false; 
            }
           Singly_Scene::ani_state = animation_state::Pause;
            break;

        case animation_state::Forward:
            if (currentStep + 1 < history.size()) 
            {
                currentStep++;
                loaded =false;  
            }
            Singly_Scene::ani_state = animation_state::Pause;
            break;

        case animation_state::Continue:
            break;
        default:
            break;         
    }
 

    if (Singly_Scene::ani_state != animation_state::Pause) elapsed_time += deltaTime;

    if(!loaded)
    {
        const auto& snapshot = history[currentStep];
        Singly_Scene::loadInfo(snapshot.info); 
        index = snapshot.index; 
        loaded = true; 
    }
    SinglyNode* ncur = Singly_Scene::Nodes.get_root(); 
    for(int i =0 ; i < index;i++)
    {
        ncur = ncur->next; 
    }
    if(ncur)ncur->SetSecondaryHighLight();
    if(currentStep != history.size()-1)
    {
        
        if(ncur->value != target)
        {
            Edge* edge; 
            auto it = std::find_if(Singly_Scene::Edges.begin(), Singly_Scene::Edges.end(),
            [ncur](Edge* edge) {
                return edge->getFrom() == ncur;
              });
            if(it != Singly_Scene::Edges.end())
            {
             edge = *it; 
            }else{
                edge =nullptr; 
            }
            if(edge)
            {   
                PolyNode* from = edge->getFrom();
                PolyNode* to = edge->getTo(); 
                 float theta = atan2(to->getPosition().y - from->getPosition().y, 
                             to->getPosition().x - from->getPosition().x);
         
                 Vector2 cpos = Vector2({Singly_Scene::Node_radius * cos(theta) + from->getPosition().x,
                                  Singly_Scene::Node_radius * sin(theta) + from->getPosition().y});
         
                 Vector2 dpos = Vector2({to->getPosition().x - Singly_Scene::Node_radius * cos(theta),
                                  to->getPosition().y - Singly_Scene::Node_radius * sin(theta)});
                Vector2 npos= Vector2(
                    {std::min(dpos.x,cpos.x+(elapsed_time/(duration/history.size()))*(dpos.x-cpos.x)),
                    std::min(dpos.y,cpos.y+(elapsed_time/(duration/history.size()))*(dpos.y- cpos.y))});
               
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
                         DrawLineEx(p1, p2, edge->getsize(), color);
                    } 
            }    
        }
        if(ncur == Singly_Scene::Nodes.get_root() && ncur->value == target)
        {
            SinglyNode* tmp =ncur; 
            ncur->SetPrimaryHighLight();
            if (elapsed_time >= duration/history.size()) {
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
                Singly_Scene::m.setDuration(duration/history.size());
                Singly_Scene::m.updateTarget(Vector2({(float)(-Singly_Scene::Node_radius*2-50),0}),tmp->next);
            }
            Singly_Scene::Nodes.size--; 
            Singly_Scene::ani =None;
            elapsed_time = 0;
            isPrerunDone = 0; 
            isDone =true ; 
            loaded = false; 
            delete tmp;
            elapsed_time = 0 ; 
            return; 
          }
        }
       
        if (ncur && ncur->next&& ncur->next->value != target) {
                if (elapsed_time >= duration/history.size()) {
                    ncur->SetSecondaryHighLight(); 
                    ncur = ncur->next;
                    currentStep++;
                    index++; 
                    elapsed_time = 0;
                }
        } else
        { 
            ncur->next->SetPrimaryHighLight(); 
            if (elapsed_time >= duration/history.size()) {
                    Singly_Scene::Nodes.DeleteNode(ncur,duration/history.size()); 
                    isDone = true;
                    Singly_Scene::ani=None;
                    isPrerunDone = 0; 
                    loaded = 0 ; 
                    elapsed_time = 0; 
            }
        }
    }else{
        if (elapsed_time >= duration/history.size()) {
            isDone = true;
            Singly_Scene::ani=None;
            isPrerunDone = 0; 
            elapsed_time = 0;
        }
    }
   
}

void Ani_LinkedListDelete::prerun()
{
    history.clear();
    Singly_Scene::code.push_back(
        "while(ncur&& ncur->next && ncur->next->value != target)\n { ncur = ncur->next; }"
        
    ); 
    if(Singly_Scene::Nodes.get_root()->value == target) 
    {
        history.push_back({0, Singly_Scene::getInfo()}); 
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
            SinglyNode* newcur = tmp->next; 
            while(newcur)
            {
                Vector2 position = newcur->getPosition(); 
                newcur->SetPosition(Vector2{-Singly_Scene::Node_radius*2 -50 + position.x, position.y});
                newcur =newcur->next; 
            }
        }
        Singly_Scene::Nodes.size--;

        delete tmp;
        history.push_back({0, Singly_Scene::getInfo()});  
        isPrerunDone = true;  
        currentStep = 0 ; 
        elapsed_time = 0;  
        Singly_Scene::loadInfo(history[0].info);
        Singly_Scene::ani_state = Pause; 
        return; 
    }
    
    Singly_Scene::code.push_back(
        "while(ncur&& ncur->next && ncur->next->value != target)\n { ncur = ncur->next; }"
        ); 
    
    SinglyNode* ncur = Singly_Scene::Nodes.get_root();
    Edge* edge= nullptr; 
    int nindex= -1; 

    while(ncur&& ncur->next && ncur->next->value != target)
    {
       
        history.push_back({++nindex,Singly_Scene::getInfo()});
        ncur = ncur->next; 
    }
    Singly_Scene::code.push_back(
    "while(ncur&& ncur->next && ncur->next->value != target)\n { ncur = ncur->next; }"
    ); 

    history.push_back({++nindex,Singly_Scene::getInfo()});
    SinglyNode* tmp = ncur->next; 
    if(tmp&&tmp->next)
    {
        
        SinglyNode* newcur = tmp->next; 
        Singly_Scene::Edges.push_back(new Edge(ncur,tmp->next));
        while(newcur)
        {
            Vector2 position = newcur->getPosition(); 
            newcur->SetPosition(Vector2{-Singly_Scene::Node_radius*2 -50 + position.x, position.y});
            newcur =newcur->next; 
        }
        Singly_Scene::Edges.erase(
            std::remove_if(Singly_Scene::Edges.begin(),Singly_Scene::Edges.end(),[tmp](Edge* edge){
                    if (edge->getFrom() == tmp || edge->getTo() == tmp) {
                        delete edge; 
                        return true;
                    }
                    return false;
                }),
        Singly_Scene::Edges.end());
        ncur->next = tmp->next;
        Singly_Scene::Nodes.size--;  
        delete tmp;
        history.push_back({++nindex,Singly_Scene::getInfo()});
    }else if(tmp){
        Singly_Scene::Edges.erase(
            std::remove_if(Singly_Scene::Edges.begin(),Singly_Scene::Edges.end(),[ncur,tmp](Edge* edge){
                    if (edge->getFrom() == ncur && edge->getTo() == tmp) {
                        delete edge; 
                        return true;
                    }
                    return false;
                }),
        Singly_Scene::Edges.end());
        Singly_Scene::Nodes.size--; 
        ncur->next = tmp->next;
        delete tmp;
        history.push_back({++nindex,Singly_Scene::getInfo()});
    }


    isPrerunDone = true;  
    currentStep = 0 ; 
    loaded = false; 
    Singly_Scene::loadInfo(history[0].info);
    duration = 0.5*history.size(); 
    Singly_Scene::maxsteps = history.size(); 
    Singly_Scene::stepindex = 0 ;  
    Singly_Scene::ani_state = Pause; 
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
void Ani_InsertRandomList::reset()
{
    elapsed_time = 0;  
    root = nullptr; 
    target = nullptr; 
    isDone  = true; 

}
void Ani_InsertRandomList::updateAnimations(float deltaTime)
{ 
    if(isDone||!target) return;
    target->Draw(); 
   if(Singly_Scene::ani_state != Pause) elapsed_time += deltaTime;
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
    if( CheckCollisionCircles(Singly_Scene::Nodes.get_root()->getPosition(),Singly_Scene::Node_radius,target->getPosition(),Singly_Scene::Node_radius))
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
void  Ani_MoveNode::reset(){
    isDone =true;
    elapsed_time =0 ;
    target = nullptr;  
} 

void Ani_MoveNode::updateAnimations(float deltaTime)
{
    if(isDone||!target)return;
    if(Singly_Scene::ani_state != Pause)  elapsed_time += deltaTime; 
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
void Ani_Straighten ::reset()
{ 
  elapsed_time= 0 ;
  isDone = true; 
} 
void Ani_Straighten::updateAnimations(float deltaTime)
{
    if(isDone)return; 
    if(Singly_Scene::ani_state != Pause)  elapsed_time += deltaTime; 
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
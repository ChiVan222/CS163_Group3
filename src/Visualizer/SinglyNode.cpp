#include "SinglyNode.h"
#include <raylib.h> 
#include <string>
#include "Scene.h"
#include "UI.h"
SinglyNode:: SinglyNode(Vector2 pos,float radius, int value):PolyNode(pos,radius),next(nullptr), value(value)
{ }

bool SinglyNode::Draw()
{  
    Color defaulta = GetColor(0x2E3192);
    Color defaule_sec = GetColor(0x1BFFFF);
    Color circle_primaryColor = (highlight == Null? defaulta :((highlight == Primary)? RED:ORANGE)); 
    DrawCircleGradient(position.x, position.y,radius, circle_primaryColor, defaule_sec);
    DrawCircleLines(position.x, position.y,radius, WHITE);
    int textSize = radius / 2;
    const char* text = std::to_string(value).c_str();
    int textWidth = MeasureText(text, textSize);
    int textHeight = textSize;
    int textX = position.x - textWidth / 2;
    int textY = position.y - textHeight / 2;
    DrawText(text,textX, textY, radius, WHITE);
    return true;
}
void SinglyNode::SetNext(SinglyNode* newNode)
{
    next = newNode;
}
int SinglyNode::getValue()
{
    return value;
}
SinglyLinkedListNode:: SinglyLinkedListNode():root(nullptr),size(0)
{

}
SinglyLinkedListNode::SinglyLinkedListNode(SinglyNode* node): root(node),size(0)
{
 
}

SinglyLinkedListNode::~SinglyLinkedListNode()
{
    DeleteList();
}
void SinglyLinkedListNode::DeleteList()
{
   while(root)
   {
     SinglyNode* tmp = root; 
     root = root->next; 
     delete tmp; 
   }   
}
SinglyNode& SinglyNode::operator=(SinglyNode&& other) noexcept {
    if (this == &other) return *this;
     next =other.next;
     value = other.value; 
    return *this;
}
#include <algorithm>
#include <iostream>
void SinglyLinkedListNode::Insert(SinglyNode* node, float duration)
{ 
    if(!root) 
    {
        root = node; 
        size++;
        return ; 
    }
    SinglyNode* cur2 = root; 
    size++;  
    while(cur2->next && cur2 != Singly_Scene::cur)
    {
        cur2 = cur2->next; 
    }
    
    if(cur2->next)
    { 
        SinglyNode* tmp = cur2->next; 
        Singly_Scene::m.setDuration(duration);
        Singly_Scene::m.updateTarget(Vector2({node->getRadius()*2 +50,0}),tmp); 

        Singly_Scene::Edges.erase(
            std::remove_if(Singly_Scene::Edges.begin(),Singly_Scene::Edges.end(),[cur2,tmp](Edge* edge){
                    if (edge->getFrom() == cur2&& edge->getTo() == tmp) {
                        delete edge; 
                        return true;
                    }
                    return false;
                }),
        Singly_Scene::Edges.end());
        cur2->next = node;
        node->next = tmp;
        Singly_Scene::Edges.push_back(new Edge(node,tmp)); 
        Singly_Scene::addFunction(2, std::bind(&Ani_DrawEdge::updateTarget, &Singly_Scene::de,Singly_Scene::Edges.back())); 

    }else{
        cur2->next = node;
    }
}
void SinglyLinkedListNode::Traverse()
{
    if(!root) return; 
    SinglyNode* cur = root; 
    while(cur)
    {
         cur->Draw(); 
         if(cur->isClicked()&& Singly_Scene::ani == None)
         {
            Singly_Scene::cur = cur;
         }
         
         cur = cur->next; 
    }

}
int  SinglyLinkedListNode::get_size(){
    return size; 
}

SinglyNode* SinglyLinkedListNode::get_root()
{
     return root;
} 

void SinglyLinkedListNode::UpdateHightLight()
{
   SinglyNode* cur= root;
   while(cur)
   { 
     if(cur == Singly_Scene::cur)
     {
        cur->SetPrimaryHighLight();
     }else{
        cur->SetNullHighLight();
     }
     cur = cur->next;
   }
}
void SinglyLinkedListNode::set_root(SinglyNode* nroot)
{
  root = nroot;

}
bool SinglyNode::isClicked()
{ 
    if(CheckCollisionPointCircle(UI::mousePos, position, radius)&&IsMouseButtonPressed(MOUSE_BUTTON_LEFT))  
    { 
         OnClicked(); 
         return true; 
    }return false; 
}
void SinglyNode::OnClicked()
{
    // Singly_Scene::cur  = this; 
}
void SinglyLinkedListNode::DeleteNode(SinglyNode* cur2, float duration)
{ 
    if(!cur2)
    {
        return ; 
    }
  
    if(cur2->next)
    { 
        SinglyNode* tmp = cur2->next; 
        if(tmp->next)
        {
            
            Singly_Scene::Edges.push_back(new Edge(cur2,tmp->next));
            Singly_Scene::addFunction(2, std::bind(&Ani_DrawEdge::updateTarget, &Singly_Scene::de,Singly_Scene::Edges.back()));
            Singly_Scene::m.setDuration(duration);
            Singly_Scene::m.updateTarget(Vector2({(float)(-Singly_Scene::Node_radius*2-50),0}),tmp->next); 
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
        cur2->next = tmp->next;
        size--;  
        delete tmp;
    }
}
#include <math.h>
float getDistance(Vector2 a, Vector2 b)
{ 
    return std::sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y)); 
}
void  SinglyNode::ForwardDistanceConstraints(float maxDistance)
{ 
    if(!next) return; 
    if(this == Singly_Scene::cur) 
    {
        BackwardDistanceConstraints(maxDistance); 
        return;
    }
    next->ForwardDistanceConstraints(maxDistance); 
    float distance = getDistance(position, next->position); 
        Vector2 direction = { (next->position.x - position.x) / distance, 
                              (next->position.y - position.y) / distance };

        position.x = next->position.x - direction.x * maxDistance;
        position.y = next->position.y - direction.y * maxDistance;
}
void  SinglyNode::BackwardDistanceConstraints(float maxDistance)
{
     if(!next) return; 
     float distance = getDistance(position, next->position); 
        Vector2 direction = { (position.x - next->position.x) / distance,
                              (position.y - next->position.y) / distance };

        next->SetPosition(Vector2({
            position.x - direction.x * maxDistance,
            position.y - direction.y * maxDistance
        }));
   next->BackwardDistanceConstraints(maxDistance);
}
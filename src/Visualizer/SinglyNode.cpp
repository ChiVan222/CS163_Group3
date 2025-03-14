#include "SinglyNode.h"
#include <raylib.h> 
#include <string>
#include "Scene.h"
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
void SinglyLinkedListNode::Insert(SinglyNode* node, float duration)
{ 
    if(!root) 
    {
        root = node; 
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
        Singly_Scene::m.updateTarget(Vector2({node->getRadius()*2 +10,0}),tmp); 
        Singly_Scene::Edges.push_back(new Edge(node,tmp)); 
        Singly_Scene::Edges.erase(
            std::remove_if(Singly_Scene::Edges.begin(),Singly_Scene::Edges.end(),[cur2,node](Edge* edge){
                    if (edge->getFrom() == cur2 || edge->getTo() == node) {
                        delete edge; 
                        return true;
                    }
                    return false;
                }),

        Singly_Scene::Edges.end());
        cur2->next = node;
        node->next = tmp;
        Singly_Scene::Edges.push_back(new Edge(cur2,node)); 

    }else{
        cur2->next = node;
        Singly_Scene::Edges.push_back(new Edge(cur2,node)); 
    }
}
void SinglyLinkedListNode::Traverse()
{
    if(!root) return; 
    SinglyNode* cur = root; 
    while(cur)
    {
         cur->Draw(); 
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

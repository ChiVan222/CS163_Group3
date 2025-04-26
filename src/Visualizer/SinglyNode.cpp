#include "SinglyNode.h"
#include <raylib.h> 
#include <string>
#include "Scene.h"
#include "UI.h"
#include <sstream>
#include <raymath.h>
SinglyNode:: SinglyNode(Vector2 pos,float radius, int nvalue):PolyNode(pos,radius),next(nullptr), value(nvalue)
{ 
    value = nvalue;
    input = std::to_string(value);
}
SinglyNode:: SinglyNode(SinglyNode* newnode):PolyNode(newnode->position,newnode->radius),next(nullptr)
{
    value = newnode->value;
    input = std::to_string(value); 
}; 
SinglyNode::SinglyNode(const SinglyNode& other)
: PolyNode(other.position,other.radius), next(nullptr)
{
       value = other.value;
    input = std::to_string(value); 
}
bool SinglyNode::Draw()
{  
    Color defaulta = GetColor(0x2E3192);
    Color defaule_sec = PolyNode::colorNode;
    std::pair<Color,Color> p =  PolyNode::GetHighlightColors3(PolyNode::colorNode); 
    Color primary_color  = p.first;
    Color secondar_color = p.second;
    Color circle_primaryColor = (highlight == Null? PolyNode::colorNode :((highlight == Primary)? primary_color:secondar_color)); 
    DrawCircleGradient(position.x, position.y,radius, circle_primaryColor, defaule_sec);
    // DrawCircle(position.x, position.y,radius, circle_primaryColor); 
    DrawCircleLines(position.x, position.y,radius, WHITE);
    const char* text = input.c_str();
    int textWidth = MeasureText(text, radius);
    int textHeight = radius;
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
        Singly_Scene::m.setDuration(0.5);
        Singly_Scene::addFunction(Singly_Scene::animation_queue,Singly_Scene::cur_animation.first,std::bind(Ani_MoveList::updateTarget,&Singly_Scene::m,Vector2({node->getRadius()*2 +50,0}),tmp));
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
        Singly_Scene::addFunction(Singly_Scene::animation_queue,Singly_Scene::cur_animation.first-1, std::bind(&Ani_DrawEdge::updateTarget, &Singly_Scene::de,Singly_Scene::Edges.back())); 

    }else{
        cur2->next = node;
    }
}
void SinglyLinkedListNode::InsertAfter(SinglyNode* prevnode, SinglyNode* node)
{
    if(!root) 
    {
        root = node; 
        size++;
        return ; 
    }
    SinglyNode* cur2 = root; 
    size++;  
    while(cur2 && cur2 != prevnode)
    {
        cur2 = cur2->next; 
    }
    if (!cur2) {
        return;
    }
    SinglyNode* tmp = cur2->next; 
    if(tmp)
    { 
        SinglyNode* newcur = tmp ;
        while(newcur)
        {
            Vector2 position = newcur->getPosition(); 
            newcur->SetPosition(Vector2{node->getRadius()*2 +50 + position.x, position.y});
            newcur =newcur->next; 
        }
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
        Singly_Scene::Edges.back()->isDraw = 1 ; 
    }else{
        cur2->next = node;
    }
}
#include <math.h>
float getDistance(Vector2 a, Vector2 b)
{ 
    return std::sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y)); 
}
void SinglyLinkedListNode::InsertAtEnd(SinglyNode* node,float maxDistance)
{ 
    if(!root) 
    {
        root = node; 
        size++;
        return ; 
    }
    SinglyNode* cur2 = root; 
    size++;  
    Vector2 direction = {1,0};

    while(cur2->next)
    {
        float distance = getDistance(cur2->next->getPosition(),cur2->getPosition());
        direction.x = (cur2->next->getPosition().x-cur2->getPosition().x)/distance;
        direction.y =  (cur2->next->getPosition().y-cur2->getPosition().y)/distance;
        cur2 = cur2->next; 
    }
    cur2->next = node;
    node->SetPosition(Vector2({ cur2->getPosition().x + direction.x * maxDistance,
        cur2->getPosition().y + direction.y * maxDistance }));

    Singly_Scene::Edges.push_back(new Edge(cur2,node)); 
    Singly_Scene::addFunction(Singly_Scene::animation_queue,Singly_Scene::cur_animation.first-1, std::bind(&Ani_DrawEdge::updateTarget, &Singly_Scene::de,Singly_Scene::Edges.back())); 

}

void SinglyLinkedListNode::InsertAtEnd2(SinglyNode* node,float maxDistance)
{ 
    if(!root) 
    {
        root = node; 
        size++;
        return ; 
    }
    SinglyNode* cur2 = root; 
    size++;  
    Vector2 direction = {1,0};

    while(cur2->next)
    {
        float distance = getDistance(cur2->next->getPosition(),cur2->getPosition());
        direction.x = (cur2->next->getPosition().x-cur2->getPosition().x)/distance;
        direction.y =  (cur2->next->getPosition().y-cur2->getPosition().y)/distance;
        cur2 = cur2->next; 
    }
    cur2->next = node;
    node->SetPosition(Vector2({ cur2->getPosition().x + direction.x * maxDistance,
        cur2->getPosition().y + direction.y * maxDistance }));

    Singly_Scene::Edges.push_back(new Edge(cur2,node)); 
    Singly_Scene::Edges.back()->isDraw = true; 
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
void SinglyLinkedListNode:: TraverseCheck()
{
    if(!root) return; 
    SinglyNode* cur = root; 
    while(cur)
    {
         if(cur->isClicked()&& Singly_Scene::ani == None)
         {
            Singly_Scene::cur = cur;
         }
          cur->OnClicked(); 
         cur = cur->next; 
    }
}
int  SinglyLinkedListNode::get_size(){
    return size; 
}

SinglyNode* SinglyLinkedListNode::get_root() const
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
void SinglyLinkedListNode::DeleteAtEnd()
{  
    if(!root && !root->next) return; 
  SinglyNode* cur = root; 
 
  while(cur&& cur->next && cur->next->next)
  {
    cur = cur->next; 
  }
  SinglyNode* tmp = cur->next;
  Singly_Scene::Edges.erase(
    std::remove_if(Singly_Scene::Edges.begin(),Singly_Scene::Edges.end(),[tmp](Edge* edge){
            if (edge->getTo() == tmp) {
                delete edge; 
                return true;
            }
            return false;
        }),
Singly_Scene::Edges.end());
  cur->next = nullptr; 
   
}   
bool SinglyNode::isClicked()
{ 
   
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointCircle(UI::mousePos, position,radius)) {
       return true;
    } else  {
        return false; 
    }
    return false; 
}
bool safe_string_to_int(const std::string& str, int& out) {
    std::istringstream iss(str);
    int val;
    if (iss >> val && iss.eof()) {
        out = val;
        return true;
    }
    return false;
}
bool SinglyNode::OnClicked()
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointCircle(UI::mousePos, position,radius)) {
        isActive = true;
    } else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        input = std::to_string(value); 
        isActive = false;
        return false; 
    }
    if(isActive)
    {
        int key =GetCharPressed();
        while(key>0)
        {       
            if(key>=32 && key<= 125 && input.size()<max_input)
            {
                input +=  (char)key; 
            }
            key = GetCharPressed();
        }
        if(GetTime() - last_deletedtime >= wait_time)
        { 
            if(IsKeyDown(KEY_BACKSPACE)&& !input.empty())
            {
                input.pop_back(); 
                last_deletedtime  = GetTime(); 
            }
        }
        if(IsKeyPressed(KEY_ENTER))
        {
                safe_string_to_int(input,value); 
        }
       
    }
    return true; 
}
void SinglyLinkedListNode::DeleteNode(SinglyNode* cur2, float duration)
{
    if(!cur2){
        return ; 
    }
    if(cur2->next)
    { 
        SinglyNode* tmp = cur2->next; 
        if(tmp->next)
        {
            
            Singly_Scene::Edges.push_back(new Edge(cur2,tmp->next));
            Singly_Scene::addFunction(Singly_Scene::animation_queue,Singly_Scene::cur_animation.first-1, std::bind(&Ani_DrawEdge::updateTarget, &Singly_Scene::de,Singly_Scene::Edges.back()));
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
void  SinglyNode::ForwardAngleConstraints(float maxAngle)
{ 
    if(!next || ! next->next) return; 
    
    if(this ==  Singly_Scene::cur||this->next == Singly_Scene::cur) 
    {
        Singly_Scene::cur->BackwardAngleConstraints(maxAngle); 
        return;
    }
    next->ForwardAngleConstraints(maxAngle); 
    Vector2 A =  position; 
    Vector2 B = next->position; 
    Vector2 C = next->next->position;
    Vector2 BA = A-B;
    Vector2 BC = C-B;
    float dotProduct = Vector2DotProduct(BA,BC); 
    float magnitudeBA = Vector2Length(BA); 
    float magnitudeBC = Vector2Length(BC);
    float cosTheta = dotProduct / (magnitudeBA * magnitudeBC);
    cosTheta = std::max(-1.0f, std::min(1.0f, cosTheta));
    float theta = acos(cosTheta);
    if (theta > maxAngle)
    {
    Vector2 AB = B - A;
    float lengthAB = Vector2Length(AB);
    float currentAngle = atan2(AB.y, AB.x);
    Vector2 AC = C - A;
    float targetAngle = (Vector2DotProduct(AB, AC) > 0) ? maxAngle : -maxAngle;
    Vector2 newB = {
        A.x + lengthAB * cos(targetAngle),
        A.y + lengthAB * sin(targetAngle)
    };
    next->SetPosition(newB);
    }
    
}
void SinglyNode::BackwardAngleConstraints(float maxAngle)
{
    if (!next || !next->next) return;
    Vector2 A =  position; 
    Vector2 B = next->position; 
    Vector2 C = next->next->position;
    Vector2 BA = A-B;
    Vector2 BC = C-B;
    float dotProduct = Vector2DotProduct(BA,BC); 
    float magnitudeBA = Vector2Length(BA); 
    float magnitudeBC = Vector2Length(BC);
    float cosTheta = dotProduct / (magnitudeBA * magnitudeBC);
    cosTheta = std::max(-1.0f, std::min(1.0f, cosTheta));
    float theta = acos(cosTheta);
    if (theta > maxAngle)
    {
        Vector2 AB = B - A;
        float lengthAB = Vector2Length(AB);
        float currentAngle = atan2(AB.y, AB.x);
        Vector2 AC = C - A;
        float targetAngle = (Vector2DotProduct(AB, AC) > 0) ? maxAngle : -maxAngle;
        Vector2 newB = {
            A.x + lengthAB * cos(targetAngle),
            A.y + lengthAB * sin(targetAngle)
        };
        next->SetPosition(newB);
    }
    next->BackwardAngleConstraints(maxAngle);
}

SinglyLinkedListNode::SinglyLinkedListNode(const SinglyLinkedListNode& other) {
    size = other.size;
    root = nullptr;

    if (!other.root) return;

    SinglyNode* currOther = other.root;
    SinglyNode* prevNew = nullptr;

    while (currOther) {
        SinglyNode* newNode = new SinglyNode(*currOther); 
        if (!root) {
            root = newNode;
        } else {
            prevNew->SetNext(newNode);
        }
        prevNew = newNode;
        currOther = currOther->next;
    }
}



#include "SinglyNode.h"
#include <raylib.h> 
#include <string>
SinglyNode:: SinglyNode(SinglyLinkedList::Node* node,Vector2 pos,float radius):PolyNode(pos,radius),node(node)
{ 
     
}
void SinglyNode::Draw()
{  
    Color defaulta = GetColor(0x2E3192);
    Color defaule_sec = GetColor(0x1BFFFF);
    Color circle_primaryColor = (highlight == Null? defaulta :((highlight == Primary)? RED:ORANGE)); 
    DrawCircleGradient(position.x, position.y,radius, circle_primaryColor, defaule_sec);
    DrawCircleLines(position.x, position.y,radius, WHITE);
    int textSize = radius / 2;
    const char* text = std::to_string(node->value).c_str();
    int textWidth = MeasureText(text, textSize);
    int textHeight = textSize;
    int textX = position.x - textWidth / 2;
    int textY = position.y - textHeight / 2;
    DrawText(text,textX, textY, radius, WHITE);
}
void SinglyNode::SetRoot(SinglyLinkedList::Node* newNode)
{
    node = newNode;
}
int SinglyNode::getValue()
{
    return node->value;
}

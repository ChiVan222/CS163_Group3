#pragma once
#include "PolyNode.h"
#include "..\DataStructures\SinglyLinkedList\SinglyLinkedList.h"
class SinglyNode: public PolyNode
{ 
    private : 
        SinglyLinkedList::Node* node; 
    public : 
        SinglyNode(SinglyLinkedList::Node* node,Vector2 pos,float radius); 
        void Draw() override; 
        void SetRoot(SinglyLinkedList::Node* node); 
        int getValue();
};

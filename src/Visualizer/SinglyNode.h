#pragma once
#include "PolyNode.h"
#include "..\DataStructures\SinglyLinkedList\SinglyLinkedList.h"
class SinglyNode: public PolyNode, SinglyLinkedList
{ 
    private : 
        Node* node; 
    public : 
        SinglyNode(Node* node,Vector2 pos,float radius); 
        void Draw() override; 
        void SetRoot(Node* newNode); 
};

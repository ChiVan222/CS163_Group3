#pragma once
#include "PolyNode.h"
class SinglyNode: public PolyNode
{ 
    public : 
        SinglyNode* next;
        int value;
    public : 
        SinglyNode(Vector2 pos,float radius, int value); 
        void SetNext(SinglyNode* newNode); 
        bool Draw() override; 
        int getValue();
        SinglyNode& operator=(SinglyNode&& other) noexcept;
};
class SinglyLinkedListNode
{  
    protected: 
      int size; 
      SinglyNode* root;  
    public :  
      SinglyLinkedListNode();
      SinglyLinkedListNode(int x);
      SinglyLinkedListNode(SinglyNode* node);
      ~SinglyLinkedListNode();
      void DeleteList();  
      int get_size();
      void Insert(SinglyNode* node,float duration); 
      SinglyNode* get_root(); 
      void Traverse();
}; 


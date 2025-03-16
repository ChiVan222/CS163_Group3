#pragma once
#include "PolyNode.h"
#include <raylib.h>   
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
        bool isClicked();
        void OnClicked(); 
        void ForwardDistanceConstraints(float maxDistance);
        void BackwardDistanceConstraints(float maxDistance);

};
class SinglyLinkedListNode
{  
   public :
     int size; 
    protected: 
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
      void set_root(SinglyNode* nroot); 

      void DeleteNode(SinglyNode* cur2, float duration); 
      void Traverse();
      void UpdateHightLight(); 

}; 


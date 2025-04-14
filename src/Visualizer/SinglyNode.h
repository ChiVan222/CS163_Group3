#pragma once
#include "PolyNode.h"
#include <string>
#include <raylib.h>   
class SinglyNode: public PolyNode
{ 
    public : 
        SinglyNode* next;
        int value;
        bool isActive = false; 
        static constexpr int max_input = 20; 
        std::string input; 
        Rectangle inputbox; 
        float wait_time = 0.1f ; 
        float last_deletedtime = 0.0f; 
    public : 
        SinglyNode(Vector2 pos,float radius, int value); 
        SinglyNode(SinglyNode* newnode); 
        SinglyNode(const SinglyNode& other);

        void SetNext(SinglyNode* newNode);
        bool Draw() override; 
        int getValue();
        SinglyNode& operator=(SinglyNode&& other) noexcept;
        bool isClicked();
        void OnClicked(); 
        void ForwardDistanceConstraints(float maxDistance);
        void BackwardDistanceConstraints(float maxDistance);
        void ForwardAngleConstraints(float maxAngle);
        void BackwardAngleConstraints(float Angle);
      
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
      SinglyLinkedListNode(const SinglyLinkedListNode& other);
        ~SinglyLinkedListNode();
        void DeleteList();  
        int get_size();
        void Insert(SinglyNode* node,float duration); 
        void InsertAtEnd(SinglyNode* node,float maxDistance);
        SinglyNode* get_root() const; 
        void set_root(SinglyNode* nroot); 

        void DeleteNode(SinglyNode* cur2, float duration); 
        void Traverse();
        void TraverseCheck();
        void DeleteAtEnd();   
        void UpdateHightLight(); 

  }; 


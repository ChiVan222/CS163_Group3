#pragma once
#include <raylib.h> 
class SinglyLinkedList
{  
    public :
       struct Node{
          int value ; 
          Node* next; 
          Node(): next(nullptr),value(0){}
          Node(int x) : next(nullptr), value(x){}
      };
    protected: 
      
      Node* root;  
    public :  
      SinglyLinkedList();
      SinglyLinkedList(int x);
      SinglyLinkedList(Node* node);

      ~SinglyLinkedList();
      void DeleteList();  
      void Traverse(Vector2 position, float radius); 
      void Traverse(Node* x,Vector2 position, float radius);
      Node* Insert(int x); 
      bool Delete(int x); 
      bool  Search(int x); 
      Node* get_root(); 
}; 

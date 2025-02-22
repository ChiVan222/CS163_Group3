#pragma once
class SinglyLinkedList
{
    private : 
      struct Node{
        int value ; 
        Node* next; 
        Node(): next(nullptr),value(0){}
        Node(int x) : next(nullptr), value(x){}
      };
      Node* root;  
    public :  
      SinglyLinkedList(): root(nullptr){}
      SinglyLinkedList(int x): root(new Node(x)){}
      ~SinglyLinkedList();
      void DeleteList();  
      void Traverse(); 
      void Traverse(Node* x);
      void Insert(int x); 
      bool Delete(int x); 
      bool  Search(int x); 
}; 

#pragma once
template<class Entry>  
class SinglyLinkedList
{
    private : 
      struct Node{
        Entry value ; 
        Node* next; 
        Node(): next(nullptr),value(Entry()){}
        Node(Entry x) : next(nullptr), value(Entry(x)){}
      };
      Node* root;  
    public :  

      SinglyLinkedList(): root(nullptr){}
      SinglyLinkedList(Entry x): root(new Node(x)){}
      ~SinglyLinkedList(){DeleteList();} 
      void DeleteList();  
      void Traverse(); 
      void Traverse(Node* x);
      void Insert(Entry x); 
      void Delete(Entry x); 
      void Delete(Node* a); 
}; 
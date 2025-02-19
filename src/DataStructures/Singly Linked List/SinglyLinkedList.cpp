#include "SinglyLinkedList.h"
#include <iostream>
template<class Entry>
void SinglyLinkedList<Entry>::DeleteList()
{
   while(root)
   {
     Node* tmp = root; 
     root = root->next; 
     delete tmp; 
   }   
}
template<class Entry> 
void SinglyLinkedList<Entry>::Insert(Entry x)
{ 
    Node* cur = root; 
    while(cur->next)
    {
        cur = cur->next; 
    }
    cur->next = new Node(x); 
}
template<class Entry> 
void SinglyLinkedList<Entry>::Traverse()
{
    Traverse(root); 
}
template<class Entry> 
void SinglyLinkedList<Entry>::Traverse(Node* x)
{
   if(!x) return; 
   std::cout<x->val<<" ";
   Traverse(x->next);
}
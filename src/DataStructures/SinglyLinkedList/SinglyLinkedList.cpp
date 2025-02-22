#include <iostream>
#include "SinglyLinkedList.h"
SinglyLinkedList::~SinglyLinkedList()
{
    DeleteList();
}
void SinglyLinkedList::DeleteList()
{
   while(root)
   {
     Node* tmp = root; 
     root = root->next; 
     delete tmp; 
   }   
}
void SinglyLinkedList::Insert(int x)
{ 
    if(!root) 
    {
        root = new Node(x);
        return;
    }
    Node* cur = root; 
    while(cur->next)
    {
        cur = cur->next; 
    }
    cur->next = new Node(x); 
}
void SinglyLinkedList::Traverse()
{
    Traverse(root); 
}
void SinglyLinkedList::Traverse(Node* x)
{
   if(!x) return;   
   std::cout<<x->value<<" ";
   Traverse(x->next);
}
bool SinglyLinkedList::Delete(int x)
{ 
    if(!root) return false; 
    if(root->value == x) 
    {
        Node* tmp = root; 
        root = root->next;
        delete tmp; 
        return true;
    }
    Node* cur = root;
    while(cur->next && cur->next->value != x)
    {
        cur = cur->next;
    } 
    if(!cur->next) return false; 
    Node* tmp = cur->next; 
    cur->next = cur->next->next; 
    delete tmp; 
    return true; 
}
bool SinglyLinkedList::Search(int x)
{
    if(!root) return false; 
    Node* cur = root; 
    while(cur)
    {
        if(cur->value == x) return true;
        cur=cur->next;

    }
    return false; 
}
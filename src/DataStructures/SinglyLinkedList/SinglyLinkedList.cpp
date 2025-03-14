#include <iostream>
#include "SinglyLinkedList.h"
#include <chrono>
#include <thread>
SinglyLinkedList::SinglyLinkedList(): root(nullptr){}
SinglyLinkedList::SinglyLinkedList(int x): root(new Node(x)){}
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
SinglyLinkedList::Node* SinglyLinkedList::Insert(int x)
{ 
    if(!root) 
    {
        root = new Node(x);
        return root;
    }
    Node* cur = root; 
    while(cur->next)
    {
        cur = cur->next; 
    }
    cur->next = new Node(x); 
    return cur->next; 
}
void SinglyLinkedList::Traverse(Vector2 position, float radius)
{
    Traverse(root,position, radius); 
}
void SinglyLinkedList::Traverse(Node* x,Vector2 position, float radius)
{
   if(!x) return;   

}
SinglyLinkedList :: SinglyLinkedList(Node* node):root(node)
{
 
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
SinglyLinkedList::Node* SinglyLinkedList::get_root()
{
  return root; 
} 

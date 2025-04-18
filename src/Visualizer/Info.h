#pragma once
#include "Edge.h"
#include "SinglyNode.h"
#include <vector>
#include <unordered_map>
struct Singly_Scene_Info{
    std::vector<Edge*> Edges;
    SinglyLinkedListNode Nodes; 
    SinglyNode* cur;  
    Singly_Scene_Info() = default;
    Singly_Scene_Info(const Singly_Scene_Info & other) {
     std::unordered_map<SinglyNode*, SinglyNode*> oldToNew;
     SinglyNode* src = other.Nodes.get_root();
     SinglyNode* prevNew = nullptr;
     while (src) {
         SinglyNode* newNode = new SinglyNode(*src);
         oldToNew[src] = newNode;
  
         if (!prevNew)
             Nodes.set_root(newNode);
         else
             prevNew->SetNext(newNode);
  
         prevNew = newNode;
         src = src->next;
     }
     Nodes.size = other.Nodes.size;
     cur  = other.cur? oldToNew[other.cur] : nullptr; 
     for (Edge* edge : other.Edges) {
         SinglyNode* origFrom = static_cast<SinglyNode*>(edge->getFrom());
         SinglyNode* origTo   = static_cast<SinglyNode*>(edge->getTo());
  
         if (oldToNew.count(origFrom) && oldToNew.count(origTo)) {
             Edge* newEdge = new Edge(oldToNew[origFrom], oldToNew[origTo]);
             newEdge->isDraw = 1;
             Edges.push_back(newEdge);
         }
     }
  }
  };
#pragma once
#include "PolyNode.h"
class Edge
{  protected :
     int size =2; 
     PolyNode* from; 
     PolyNode* to; 
   public :
     bool isDraw; 
  public : 
     Edge(PolyNode* from , PolyNode* to);
     bool Draw();
     PolyNode* getFrom();
     PolyNode* getTo(); 
     int getsize(); 
}; 


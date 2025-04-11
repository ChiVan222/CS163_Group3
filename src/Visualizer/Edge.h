#pragma once
#include "PolyNode.h"
class Edge
{  protected :
     int size =2; 
     PolyNode* from; 
     PolyNode* to; 
   public :
     bool isDraw; 
     int weight;
  public : 
     Edge(PolyNode* from , PolyNode* to);
     bool Draw(Color color, int flat); //1 for Graph (weight), 0 for others
     PolyNode* getFrom();
     PolyNode* getTo(); 
     int getsize(); 
}; 



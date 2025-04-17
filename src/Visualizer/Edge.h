#pragma once
#include "PolyNode.h"
class Edge
{  protected :
     int size =4; 
     PolyNode* from; 
     PolyNode* to; 
     Color color ;  
   public :
     bool isDraw; 
     int weight;
  public : 
     Edge(PolyNode* from , PolyNode* to);
     bool Draw(Color color, int flat); //1 for Graph (weight), 0 for others
     bool TrieDraw();
     PolyNode* getFrom();
     PolyNode* getTo(); 
     Color getColor();
     void setColor(Color ncolor); 
     void setSize(int size); 
     int getsize(); 

}; 



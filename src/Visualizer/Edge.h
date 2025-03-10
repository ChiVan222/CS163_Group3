#include "PolyNode.h"
class  Edge
{ protected :
     int size; 
     PolyNode* from; 
     PolyNode* to; 
  public : 
     explicit Edge(PolyNode* from , PolyNode* to);
     void Draw(); 
}; 
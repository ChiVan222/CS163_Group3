#pragma once
#include "../DataStructures/SinglyLinkedList/SinglyLinkedList.h"
#include "../DataStructures/Graph/Graph.h"
#include "SinglyNode.h"
#include "GraphNode.h"
// #include "TrieNode.h"
#include "Edge.h"
#include <vector>

  class Animations {
  protected:
      float elapsed_time;
      float duration;
      bool isDone;
  public:
      virtual void updateAnimations(float deltaTime) = 0;
      virtual void play() = 0;
      bool getState();
      int getDuration();
      void setDuration(float newduration);
      // virtual void Draw() = 0;
      explicit Animations(float duration);
  };

class Ani_DrawEdge:public Animations
{
  private: 
    Edge* target; 
  public : 
   Ani_DrawEdge(); 
   Ani_DrawEdge(float duration); 

   void updateAnimations(float deltaTime) override;
   void play() override;
   void updateTarget(Edge* egde);
}; 

class Ani_Switch:public Animations{
  public:
    Vector2 startPos = {1185,45};
    Vector2 targetPos = {1235,45};
  public:
    Ani_Switch();
    void updateAnimations(float deltaTime);
    void play();
};
  
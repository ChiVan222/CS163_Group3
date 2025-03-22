#pragma once
#include "../DataStructures/SinglyLinkedList/SinglyLinkedList.h"
#include "../DataStructures/Graph/Graph.h"
#include "SinglyNode.h"
#include "GraphNode.h"
#include "TrieNode.h"
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
      void setDuration(float newduration);
      // virtual void Draw() = 0;
      explicit Animations(float duration);
  };

class Ani_LinkedListSearching : public Animations {
private:
    int target;  
    int index; 
public:
    Ani_LinkedListSearching();
    Ani_LinkedListSearching(float duration, int target);
    void updateAnimations(float deltaTime) override;
    void updateTarget(int x);
    void play() override;
    // void Draw() override;
    Ani_LinkedListSearching& operator=(Ani_LinkedListSearching&& other) noexcept;
};
class Ani_LinkedListInsert : public Animations{
  private: 
    float radius;
    Vector2 position;
    int target;
    SinglyNode* node_insert; 
    Vector2 src_pos;
  public :  
    void updateAnimations(float deltaTime) override;
    void play() override;
    // void Draw() override;
    Ani_LinkedListInsert(float duration, int target, int radius, Vector2 position);
    Ani_LinkedListInsert();
    
    Ani_LinkedListInsert& operator=(Ani_LinkedListInsert&& other) noexcept;
    void updateTarget(int x, int radius, Vector2 position);
};
class Ani_LinkedListDelete: public Animations 
{ 
  private: 
    int target;
  public :  
    void updateAnimations(float deltaTime) override;
    void play() override;
    // void Draw() override;
    Ani_LinkedListDelete(float duration, int target);
    Ani_LinkedListDelete();
    Ani_LinkedListDelete& operator=(Ani_LinkedListDelete&& other) noexcept;
    void updateTarget(int x);
} ; 
class Ani_MoveList: public Animations{
   private: 
     Vector2 offset; 
     SinglyNode* root;  
   public : 
    void updateAnimations(float deltaTime) override;
    void play() override;
    Ani_MoveList(float duration, Vector2 offset); 
    Ani_MoveList(); 

    void updateTarget(Vector2 newoffset, SinglyNode* node);
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

class Ani_TrieInsert : public Animations {
  private:
      TrieNodePrimary* node_insert;
      Vector2 startPos;
      Vector2 targetPos;
      float radius;
      bool inserted;

  public:
      Ani_TrieInsert();
      Ani_TrieInsert(float duration);
  
      void updateTarget(Vector2 targetPos, float radius, TrieNodePrimary* node);
      void play() override;
      void updateAnimations(float deltaTime) override;
      bool isInserted() const;
      TrieNodePrimary* getNode() const;
      void setDuration(float nduration);
  };
  
  class Ani_TrieDelete : public Animations{
    private:

  };

#pragma once
#include "Animation.h"
#include "TrieNode.h"
#include "Edge.h"

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
    public:
    Ani_TrieDelete();
    void play();
    void updateAnimations(float deltaTime);
   };

   class Ani_TrieSearch : public Animations{
    public:
    string key;
    Ani_TrieSearch();
    Ani_TrieSearch(float duration);
    void play();
    void updateAnimations(float deltaTime);
    void setKey(const string word);

  };

  class Ani_TrieUpdate : public Animations{
    public:
    Ani_TrieUpdate();
    void play();
    void updateAnimations(float deltaTime);
   };

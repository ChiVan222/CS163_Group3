#pragma once
#include "Animation.h"
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
class Ani_InsertRandomList : public Animations{
    private : 
        SinglyNode* root;  
        SinglyNode* target;  
        Vector2 startpos; 
    public : 
        void updateAnimations(float deltaTime) override;
        void play() override;
        Ani_InsertRandomList(float duration); 
        void updateTarget(SinglyNode* node);  

};
class Ani_MoveNode : public Animations{ 
  private : 
    Vector2 startpos; 
    Vector2 endpos; 
    SinglyNode* target; 
  public : 
  void updateAnimations(float deltaTime) override;
  void play() override;
  Ani_MoveNode(float duration); 
  void updateTarget(SinglyNode* node,Vector2 endpos);  
}; 
class Ani_Straighten: public Animations{
  private : 
    Vector2 endpos;
  public : 
     void updateAnimations(float deltaTime) override;
     void play() override;
     Ani_Straighten(float duration); 
     void updateTarget(Vector2 endpos); 
};
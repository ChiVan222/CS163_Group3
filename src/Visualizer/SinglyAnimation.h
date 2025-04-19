#pragma once
#include "Animation.h"

#include "Info.h"
class Ani_LinkedListSearching : public Animations {
    private:
        int target;  
        int index; 
        int currentStep = -1 ; 
        bool isPrerunDone = false; 
        struct Searching_SnapShot{
          SinglyNode* cur ;
          Edge* edge;  
      }; 
    public:
        Ani_LinkedListSearching();
        Ani_LinkedListSearching(const Ani_LinkedListSearching&) = default;
        Ani_LinkedListSearching(float duration, int target);
        void updateAnimations(float deltaTime) override;
        void updateTarget(int x);
        void play() override;
        void prerun(); 
        // void Draw() override;
        Ani_LinkedListSearching& operator=(Ani_LinkedListSearching&& other) noexcept;
        Ani_LinkedListSearching& operator=(const Ani_LinkedListSearching& other) noexcept;
        std::vector<Searching_SnapShot> history;  

};
    class Ani_LinkedListInsert : public Animations{
      private: 
        float radius;
        Vector2 position;
        int target;
        Vector2 src_pos;
        int currentStep = -1;  
        SinglyNode* cur; 
        bool inserted =false; 
        int index= 0 ; 
        bool loaded = false; 
        bool isPrerunDone = false;  
        struct Insert_SnapShot{
          int index;  
          Singly_Scene_Info info;   
      }; 
      public :  
      SinglyNode* node_insert; 
      SinglyNode* insertnode = nullptr; 
        void updateAnimations(float deltaTime) override;
        void play() override;
        // void Draw() override;
        Ani_LinkedListInsert(float duration, int target, int radius, Vector2 position);
        Ani_LinkedListInsert();
        void prerun(); 
        void reset(); 
        Ani_LinkedListInsert& operator=(const Ani_LinkedListInsert& other) noexcept;
        void updateTarget(int x, int radius, Vector2 position);
        std::vector<Insert_SnapShot> history;  
    };
    class Ani_LinkedListDelete: public Animations 
    { 
      private: 
        int target;
        SinglyNode* cur; 
        bool inserted =false; 
        bool loaded = false; 
        bool isPrerunDone = false;  
        int currentStep = -1;  
        int index= -1; 
        struct Insert_SnapShot{
          int index ; 
          Singly_Scene_Info info;   
      }; 
      public :  
        void updateAnimations(float deltaTime) override;
        void play() override;
        void prerun() ; 
        // void Draw() override;
        Ani_LinkedListDelete(float duration, int target);
        Ani_LinkedListDelete();
        Ani_LinkedListDelete& operator=(const Ani_LinkedListDelete& other) noexcept;
        std::vector<Insert_SnapShot> history;  

        void updateTarget(int x);
    } ; 
    class Ani_MoveList: public Animations{
       private: 
         Vector2 offset; 
       public : 
       SinglyNode* root;  

        void updateAnimations(float deltaTime) override;
        void play() override;
        Ani_MoveList(float duration, Vector2 offset); 
        Ani_MoveList(); 
        Ani_MoveList& operator=(const Ani_MoveList& other) noexcept;
        void updateTarget(Vector2 newoffset, SinglyNode* node);
    };
class Ani_InsertRandomList : public Animations{
    private : 
        SinglyNode* root;  
        Vector2 endpos; 
        Vector2 startpos; 
    public : 
         SinglyNode* target;  
        void updateAnimations(float deltaTime) override;
        void play() override;
        Ani_InsertRandomList(float duration); 
        Ani_InsertRandomList();
        void reset(); 
        Ani_InsertRandomList& operator=(const Ani_InsertRandomList& other) noexcept;

        void updateTarget(Vector2 position, int value);  

};
class Ani_MoveNode : public Animations{ 
  private : 
    Vector2 startpos; 
    Vector2 endpos; 
  public : 
  SinglyNode* target; 

  void updateAnimations(float deltaTime) override;
  void play() override;
  Ani_MoveNode(float duration); 
  Ani_MoveNode(); 
  void reset(); 
  void updateTarget(SinglyNode* node,Vector2 endpos);  

  Ani_MoveNode& operator=(const Ani_MoveNode& other) noexcept;
}; 
class Ani_Straighten: public Animations{
  private : 
    Vector2 endpos;
  public : 
     void updateAnimations(float deltaTime) override;
     void play() override;
     Ani_Straighten(float duration); 
     Ani_Straighten(); 
     Ani_Straighten& operator=(const Ani_Straighten& other) noexcept;
     void reset(); 
     void updateTarget(Vector2 endpos); 
};
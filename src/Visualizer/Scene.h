#include "PolyNode.h"
#include "InputField.h"
#include <vector> 
#include "Ultility.h"
#include "Button.h" 
#include "Animation.h"
#include <queue>
#include <functional>
#pragma once
class Scene
{ 
    public: 
      virtual void run(Scenes& mscene)= 0; 
}; 
class SceneManager
{
  public:
 
  private: 
    Scenes mscene; 
    std::vector<Scene*> scenes;  
  public: 
    Scenes get_scene();
    void set_scene(Scenes s);
    void runScene();
    SceneManager();
    ~SceneManager();
};
class NodeScene: public Scene{
    protected :
    //  std::vector<PolyNode*> Node; 
     std::string buffer; 
     std::vector<InputField*> Inputs; 
    public :
    void DrawCommonUI(); 
    NodeScene(); 
    virtual void CheckBuffer()=0; 
}; 
class Welcome_Scene: public Scene
{
    public :
     void run(Scenes& mscene); 
};
class Menu_Scene: public Scene
{ 
    protected: 
        std::vector<Button*> Buttons; 
        std::vector<SceneButton*> sButtons;
   public : 
     void run(Scenes& mscene); 
     Menu_Scene();
     ~Menu_Scene();
};

struct FunctionComparator {
  bool operator()(const std::pair<int, std::function<void()>>& a, 
                  const std::pair<int, std::function<void()>>& b) {
      return a.first < b.first;  
  }
};
class Singly_Scene:public NodeScene
{
    public :
   static std::priority_queue<std::pair<int, std::function<void()>>, 
     std::vector<std::pair<int, std::function<void()>>>, 
    FunctionComparator> animation_queue;
        Ani_LinkedListSearching a;
        Ani_LinkedListInsert i; 
        Ani_LinkedListDelete d; 
        static Ani_DrawEdge de; 
        static Ani_MoveList m ;
        static SinglyNode* cur;
        static std::vector<Edge*> Edges;
        static bool created; 
        static SinglyLinkedListNode Nodes; 
        static animation ani; 
        static int Node_radius; 
    public: 
        void CheckBuffer() override; 
        void run(Scenes& mscene); 
        Singly_Scene();
        void Draw();
        static void addFunction(int priority, std::function<void()> func);
        void executeFunctions();

};


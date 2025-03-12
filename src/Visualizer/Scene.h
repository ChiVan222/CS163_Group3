#include "PolyNode.h"
#include "InputField.h"
#include <vector> 
#include "Ultility.h"
#include "Button.h" 
#include "Animation.h"
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
     std::vector<InputField*> Inputs; 
    public :
    void DrawCommonUI(); 
    NodeScene(); 
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
class Singly_Scene:public NodeScene
{
    protected :
        Ani_LinkedListTraversal a;
        SinglyLinkedList list;
        bool created; 
    public: 
        void run(Scenes& mscene); 
        Singly_Scene();
};
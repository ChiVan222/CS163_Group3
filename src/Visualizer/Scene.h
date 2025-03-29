#pragma once

#include "PolyNode.h"
#include "InputField.h"
#include <vector> 
#include "Ultility.h"
#include "Button.h" 
#include "Animation.h"
#include "GraphAnimation.h"
#include "SinglyAnimation.h"
#include <queue>
#include <functional>
#include <algorithm>
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
        bool isDragging;
        Ani_LinkedListInsert insert; 
        Ani_LinkedListDelete d; 
        Ani_Straighten st; 
        Ani_InsertRandomList insert_2; 
        static Ani_DrawEdge de; 
        static Ani_MoveList m ;
        static SinglyNode* cur;
        static Ani_MoveNode mn ;   
        static std::vector<Edge*> Edges;
        static bool created; 
        static SinglyLinkedListNode Nodes; 
        static animation ani; 
        static int Node_radius; 
    public: 
        void CheckBuffer() override; 
        std::vector<Button*> buttons ;   
        void run(Scenes& mscene); 
        Singly_Scene();
        void Draw();
        static void addFunction(int priority, std::function<void()> func);
        void executeFunctions();
};

class Graph_Scene: public NodeScene 
{
  public:
    static std::vector<GraphNode*> graphNodes;
    static std::vector<Edge*> Edges; 
    bool created;
    Ani_GraphInsert ani_insert;
  public:
    void CheckBuffer() override;
    void run(Scenes& mscene);
    Graph_Scene();
    ~Graph_Scene();
    void Draw();
    GraphNode* findNodeByVal(int value);
    void AddNode(Vector2 position, int value);
    void AddEdge(int from, int to, int weight);
    // void RemoveNode(int value);
};

// class Trie_Scene:public NodeScene{
//   public :
//         static Ani_TrieInsert i;
//         static std::vector<Edge*> edges;
//         static animation ani; 
//         static int Node_radius; 
//         TrieNodePrimary* cur;
//         float deltaTime;
//         static TrieNodePrimary* proot;
//         std::queue<std::string> insertQueue;  // Hàng đợi từ cần insert
//         bool isInserting = false;   
        
//     public: 
//         void CheckBuffer() override; 
//         void run(Scenes& mscene); 
//         Trie_Scene();
//         void Draw();
//         void Insert(const char& word, float duration);
      
// };
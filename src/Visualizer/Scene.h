#pragma once

#include "PolyNode.h"
#include "InputField.h"
#include <vector> 
#include <map>
#include "Ultility.h"
#include "Button.h" 
#include "Animation.h"
#include "GraphAnimation.h"
#include "SinglyAnimation.h"
#include "TrieAnimation.h"
#include <queue>
#include <functional>
#include <algorithm>
#pragma once
class Scene
{ 
  public:
      static Switch modeSwitch;
      static bool isDarkMode;
      Color dark1{27,79,58,255};
      Color dark2{29,32,30,255};
      Color light1{80,153,123,255};
      Color light2{25,32,39,255};
      Ani_Switch sw;
  
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
     std::vector<Button*>  buttons;  
     animation_state ani_state; 
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
    static std::priority_queue<std::pair<int, std::function<void()>>, 
    std::vector<std::pair<int, std::function<void()>>>, 
   FunctionComparator> UI_animation_queue;
      static int cur_priority;  
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
        void run(Scenes& mscene); 
        Singly_Scene();
        void Draw();
        static void addFunction(std::priority_queue<std::pair<int, std::function<void()>>, 
        std::vector<std::pair<int, std::function<void()>>>, 
       FunctionComparator>& q, int priority, std::function<void()> func);
        void executeFunctions(std::priority_queue<std::pair<int, std::function<void()>>, 
        std::vector<std::pair<int, std::function<void()>>>, 
       FunctionComparator>& q);
       void UI_executeFunctions();
};

class Graph_Scene: public NodeScene 
{
  public:
    Graph_Scene();
    ~Graph_Scene();
    void run(Scenes& mscene);
    void Draw();
    void CheckBuffer() override;
    GraphNode* findNodeByVal(int value);
    void AddNode(int value);
    void AddEdge(int from, int to, int weight);
    void randomize(int nodes);
    void clear();
    void runDijkstra(int start);

    static std::vector<GraphNode*> graphNodes;
    static std::vector<Edge*> Edges; 
    static std::priority_queue<std::pair<int, std::function<void()>>, 
                               std::vector<std::pair<int, std::function<void()>>>, 
                               FunctionComparator> animation_queue;
    static animation ani;

  private:
    bool created;
    bool isDragging;
    GraphNode* draggedNode;
    void draggingNode();
    Ani_GraphInsert ani_insert;
    Ani_GraphSearch ani_search;
    Ani_GraphRemove ani_remove;
    Ani_Dijkstra ani_dijkstra;
    void addFunction(std::priority_queue<std::pair<int, std::function<void()>>, 
                     std::vector<std::pair<int, std::function<void()>>>,
                     FunctionComparator>& q, int priority, std::function<void()> func); 
    void executeFunctions(std::priority_queue<std::pair<int, std::function<void()>>, 
                          std::vector<std::pair<int, std::function<void()>>>, 
                          FunctionComparator>& q);

};

 class Trie_Scene:public NodeScene{
     public :
         static Ani_TrieInsert i;
          Ani_TrieSearch s;
          Ani_TrieDelete d;
          Ani_TrieUpdate u;
           static std::vector<Edge*> edges;
         unordered_map <int, vector<TrieNodePrimary*>> levelMap;
         static animation ani;
         static int Node_radius;
         TrieNodePrimary* cur;
         TrieNodePrimary* balancePointer;
           float deltaTime;
          std::queue<TrieNodePrimary*> deleteQueue;
          static TrieNodePrimary* proot;
  
           bool isInserting = false;
  
      public:
          void CheckBuffer() override;
          void run(Scenes& mscene);
          Trie_Scene();
        void Draw();
          void Insert(const char& word, float duration);
         bool Search(const string word,float duration);
          bool removeWord(TrieNodePrimary* node, const string& word, int depth);
          void deleteNode();
          bool isTmpPresent(TrieNodePrimary* tmp);
          void balance(int level);
          Vector2 calculatePosition(int level, int index);
           int calculateIndex(int level, const char word);
};
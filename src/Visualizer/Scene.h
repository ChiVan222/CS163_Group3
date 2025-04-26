#pragma once

#include "PolyNode.h"
#include "InputField.h"
#include <vector> 
#include <map>
#include "Utility.h"
#include "Button.h" 
#include "Animation.h"
#include "GraphAnimation.h"
#include "SinglyAnimation.h"
#include "TrieAnimation.h"
#include "tinyfiledialogs.h"
#include <fstream>
#include <queue>
#include <functional>
#include <algorithm>
#include <stack>
#include "Info.h"
#include "HeapAnimation.h"
#include "CommonUI.h"
#pragma once
class Scene
{ 
  public:
      static SettingButton setting;
      static bool isDefault;
      static Font currentFont;
      static bool isDarkMode;
      Color dark1{27,79,58,255};
      Color dark2{29,32,30,255};
      Color light1{126,130,56,255};
      Color light2{62,153,116,255};
      Color darkBar{46,46,46,255};
      Color lightBar1{60,171,126,255};
      Color lightBar2{29,32,30,255};
  
    public: 
      virtual void run(Scenes& mscene)= 0;  
      void Drawbackground();
      float sceneWidth;
      float sceneHeight;
      bool firstEntry;
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
     std::vector<PolyNode*> Node; 
    int type= 0  ;  
    ProgressBar progressBar;

    ButtonNew  createButton;
    bool isCreateChosen;
    ButtonNew randomButton;
    ButtonNew loadFileButton;
    bool isSearchChosen = false;

    ButtonNew pushButton;
    ButtonNew searchButton;

    bool isPushChosen;
    ButtonNew deleteButton;
    bool isDeleteChosen;
    InputStr inputNumber;
    ButtonNew playButton;
    std::string buffer; 
    std::vector<InputField*> Inputs; 
    std::vector<Button*>  buttons;  
    float speed; 
    public :
    static std::vector<string>  code;  
    static std::vector<int> highlights_code;
    static int stepindex;   
    static int maxsteps;
   static string info ;
    public:
    void updateStep(int index);
    void createFromFile();
    void drawButtons();
    virtual int handle() = 0;
    void DrawCommonUI(); 
    NodeScene(); 
    virtual void CheckBuffer()=0; 
    
}; 
class Welcome_Scene: public Scene
{
    public :
    Welcome_Scene();
    void run(Scenes& mscene); 
    int fontSize;
    Vector2 text1Pos;
    Vector2 text2Pos;
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
     int menuFont;
     Vector2 buttonPos;
     Vector2 menuPos;
};
class Setting_Scene :public Scene{
  public:
    TrieNodePrimary* node;
    std::vector<const char*> mytheme {"LIGHT", "DARK"};
    std::vector<const char*> font {"DEFAULT", "NORWESTER"};
    std::vector<Slider*> sliders;
    std::vector<ControlButton> controls;
    std::vector<Spinner> spinners;
    //Test code Block
    CodeBlock block;
  public:
    Setting_Scene();
    void run(Scenes& mscene);
    void TextDraw();
};

struct FunctionComparator {
  bool operator()(const std::pair<int, std::function<void()>>& a, 
                  const std::pair<int, std::function<void()>>& b) {
      return a.first > b.first;  
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
   static std::pair<int, std::function<void()>> cur_animation;
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
        static std::stack<std::pair<int, std::function<void()>>>  ani_his;
        static std::stack<std::pair<int, std::function<void()>>>  ani_replay_his;
        static std::queue<std::pair<int, std::function<void()>>>  pending_animation;
        static animation_state ani_state;  
        
        std::stack<Singly_Scene_Info> scene_info_his;
        std::stack<Singly_Scene_Info> scene_info_replay_his; 
    public: 
        void CheckBuffer() override; 
        void run(Scenes& mscene); 
        Singly_Scene();
        void Clear(); 
        void Draw();
      
        static void addFunction(std::priority_queue<std::pair<int, std::function<void()>>, 
        std::vector<std::pair<int, std::function<void()>>>, 
       FunctionComparator>& q, int priority, std::function<void()> func);
        void executeFunctions(std::priority_queue<std::pair<int, std::function<void()>>, 
        std::vector<std::pair<int, std::function<void()>>>, 
       FunctionComparator>& q);
       static void ClearHistory();
       void UI_executeFunctions();
       void executeBackwardFunction(); 
      int handle() override; 
      static Singly_Scene_Info getInfo();
       static void loadInfo(Singly_Scene_Info&& info); 
      static void loadInfo(const Singly_Scene_Info& info); 
};

struct FunctionComparator2 {
  bool operator()(const std::pair<int, std::function<void()>>& a, 
                  const std::pair<int, std::function<void()>>& b) {
      return a.first < b.first;  
  }
};

class Graph_Scene: public NodeScene 
{
  public:
    Graph_Scene();
    ~Graph_Scene();
    void run(Scenes& mscene);
    void Draw();
    void DrawButtons();
    void CheckBuffer() override;
    GraphNode* findNodeByVal(int value);
    void AddNode(int value);
    void AddEdge(int from, int to, int weight);
    void randomize(int nodes);
    void clear();
    void loadFromFile();
    int handle() override{return 0;}; 

    static std::vector<GraphNode*> graphNodes;
    static std::vector<Edge*> Edges; 
    static std::priority_queue<std::pair<int, GraphNode*>, std::vector<std::pair<int, GraphNode*>>, std::greater<>> pq;
    static std::priority_queue<std::pair<int, std::function<void()>>, 
                               std::vector<std::pair<int, std::function<void()>>>, 
                               FunctionComparator2> animation_queue;
    static animation ani;
    static animation_state ani_state;

  private:
    bool created;
    bool isDragging;
    GraphNode* draggedNode;
    void draggingNode();
    void drawDescription();
    Ani_GraphInsert ani_insert;
    Ani_GraphSearch ani_search;
    Ani_GraphRemove ani_remove;
    Ani_Dijkstra ani_dijkstra;
    void addFunction(std::priority_queue<std::pair<int, std::function<void()>>, 
                     std::vector<std::pair<int, std::function<void()>>>,
                     FunctionComparator2>& q, int priority, std::function<void()> func); 
    void executeFunctions(std::priority_queue<std::pair<int, std::function<void()>>, 
                          std::vector<std::pair<int, std::function<void()>>>, 
                          FunctionComparator2>& q);

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
          void checkBalance(int level);
          Vector2 calculatePosition(int level, int index);
           int calculateIndex(int level, const char word);
           int handle() override{return 0 ;}; 

};

class Heap_Scene: public NodeScene
{
  private:
  MaxHeapVisualize maxHeap = MaxHeapVisualize();
  TittleButton tittle = TittleButton({465, 34, 350, 40}, "Max Heap", -1, BLACK, 20);

  public:
  int handle() override{return 0 ;}; 

  void run(Scenes& mscene);
  void Draw();
  void CheckBuffer() override; 
};
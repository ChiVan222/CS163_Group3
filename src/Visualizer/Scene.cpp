#include "Scene.h"
#include "UI.h"
#include <raymath.h>
Ani_MoveList Singly_Scene::m ;
Ani_MoveNode Singly_Scene::mn(0.5);
SinglyLinkedListNode Singly_Scene::Nodes = SinglyLinkedListNode();
std::vector<Edge*>Singly_Scene::Edges;
SinglyNode* Singly_Scene::cur =nullptr;
int Singly_Scene::cur_priority;
bool Singly_Scene::created = false; 

animation Singly_Scene:: ani = None; 
Ani_DrawEdge Singly_Scene::de;  
std::priority_queue<std::pair<int, std::function<void()>>, 
     std::vector<std::pair<int, std::function<void()>>>, 
    FunctionComparator> Singly_Scene:: animation_queue ; 
    std::priority_queue<std::pair<int, std::function<void()>>, 
    std::vector<std::pair<int, std::function<void()>>>, 
   FunctionComparator> Singly_Scene:: UI_animation_queue ; 
int Singly_Scene::Node_radius = 20; 
Scenes SceneManager::get_scene()
{
    return mscene;
}
void SceneManager::set_scene(Scenes s)
{
    mscene = s; 
}
void SceneManager::runScene()
{
     scenes[mscene]->run(mscene); 
}

void Welcome_Scene::run(Scenes& mscene)
{

    ClearBackground(DARKBLUE);
    Rectangle src = { 0, 0, (float)UI::background.width, (float)UI::background.height};
    Rectangle dest = { 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()};
    DrawTexturePro(UI::background, src, dest, Vector2({0, 0}), 0.0f, WHITE);
    DrawText("DATA STRUCTURE VISUALIZATION", 200, 200, 40, WHITE);
    UI::DrawFadingText(UI::time,200,UI::wHeight-200,30, "Press any keys to continue");
    if(GetKeyPressed()!=0)
    {
       mscene = Menu; 
    }
}
Menu_Scene::Menu_Scene()
{
    sButtons.push_back(new SceneButton("../assets/Images/SinglyLinkedList.png", Vector2({UI::wWidth / 5 * 1, 300}),Vector2({200,200}), "Singly Linked List",Singly));
    sButtons.push_back(new SceneButton("../assets/Images/holder.png", Vector2({UI::wWidth / 5 * 2, 300}),Vector2({200,200}), "Trie",Trie));
    sButtons.push_back(new SceneButton("../assets/Images/holder.png", Vector2({UI::wWidth / 5 * 3, 300}),Vector2({200,200}), "Heap",Heap));
    sButtons.push_back(new SceneButton("../assets/Images/holder.png", Vector2({UI::wWidth / 5 * 4, 300}),Vector2({200,200}),"Graph",Graph));
}
Menu_Scene::~Menu_Scene() {
    for (Button* button : Buttons) {
        delete button;
    }
    Buttons.clear();

    for (SceneButton* sButton : sButtons) {
        delete sButton;
    }
    sButtons.clear();

}
void Menu_Scene::run(Scenes& mscene)
{
    ClearBackground(DARKBLUE);
    DrawText("Menu", static_cast<int>(UI::wWidth/2), 100, 40, WHITE);
    for(int i = 0; i <sButtons.size();  i++)
    {
        sButtons[i]->Draw();
        sButtons[i]->DrawButtonText_below();

        if(sButtons[i]->IsHovered(UI::mousePos))
        {
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                mscene = sButtons[i]->getButtonScenes(); 
        }
    }
    if(IsKeyPressed(KEY_LEFT))
    {
         mscene = Welcome;
    }
}
#include <sstream>
#include <iostream>
void Singly_Scene::addFunction(std::priority_queue<std::pair<int, std::function<void()>>, 
std::vector<std::pair<int, std::function<void()>>>, 
FunctionComparator>& q,int priority, std::function<void()> func)
{
    q.push({priority, func});
}
void Singly_Scene::executeFunctions(std::priority_queue<std::pair<int, std::function<void()>>, 
std::vector<std::pair<int, std::function<void()>>>, 
FunctionComparator>& q)
{
    while (!q.empty()&& ani == None) {
        auto topFunction = q.top();
        q.pop();
        topFunction.second();  
    }
}
void Singly_Scene::UI_executeFunctions()
{ 
    //   while (!UI_animation_queue.empty()) {
    //         auto topFunction = UI_animation_queue.top();
    //         if(topFunction.first == cur_priority){ 
    //             UI_animation_queue.pop();
    //             topFunction.second();  
    //         }else 
    //         { 
    //              if(ani == None)
    //              { 
    //                 cur_priority = topFunction.first; 
    //              }
    //              else break;  
    //         }
    //     }
    while (!UI_animation_queue.empty()) {
        auto topFunction = UI_animation_queue.top();
        UI_animation_queue.pop();
        topFunction.second();  
    }
}

void Singly_Scene::CheckBuffer()
{
    int type;
    std::stringstream ss(buffer);
    bool inputted =false; 
    if(ani == None) 
    {
        ss>>type; 
        inputted =true;
    }
    switch(type)
    {
      case 0 :
        {   
            int x ;
            Vector2 insert_pos; 
            if(Nodes.get_root())
            {
                insert_pos = Vector2({cur->getPosition().x + 2*cur->getRadius()+50, cur->getPosition().y});
            }
            else 
            {
                insert_pos = Vector2({300,300});
            }
            if(insert.getState())
            {
                ss>>x; 
                addFunction(animation_queue,1, std::bind(&Ani_LinkedListInsert::updateTarget, &insert, x, 20, insert_pos));          
           }
        }
        break;
      case 1: 
        {
            int x ;
            if(d.getState())
            {
                ss>>x; 
                addFunction(animation_queue, 1, std::bind(&Ani_LinkedListDelete::updateTarget, &d, x));          
            }
        }
        break;
      case 3:
        { 
            if(a.getState())
            {
                int x ;
                ss>>x; 
               addFunction(animation_queue,1, std::bind(&Ani_LinkedListSearching::updateTarget, &a, x)); 
            }
        }
        break; 
    }
    if(inputted)
    {
        std::string newBuffer;
        std::string word;
        while (ss >> word) {  
            newBuffer += word + " ";
        }
        buffer = newBuffer; 
        inputted =false;
    }
}
void Singly_Scene::Draw() {
    Nodes.Traverse(); 
    for (int i = 0; i <Edges.size();i++) {
        if(Edges[i]->isDraw)Edges[i]->Draw();
    }
}
#include "iostream"
void Singly_Scene::run(Scenes& mscene)
{
   
    ClearBackground(BLACK);
    float deltaTime = IsWindowFocused() ? GetFrameTime() : 0;
    deltaTime *= ani_state; 
    CheckBuffer();
    if (IsKeyPressed(KEY_LEFT)) {
        mscene = Menu;
        created = false;
        a = Ani_LinkedListSearching(0.3,0);
        Nodes.DeleteList();
        for(int i =0; i<Edges.size();i++)
        {
             Edge* tmp = Edges[i];
             Edges[i] = nullptr;
             delete tmp;
        }
        Edges.clear();
        UI::resetCamera(); 
        ani = None;
        cur = nullptr; 
        return; 

    }
    BeginMode2D(UI::camera);
    UI::mousePos =  GetScreenToWorld2D(GetMousePosition(), UI::camera);
    a.updateAnimations(deltaTime);
    insert.updateAnimations(deltaTime); 
    m.updateAnimations(deltaTime); 
    d.updateAnimations(deltaTime);
    de.updateAnimations(deltaTime);
    mn.updateAnimations(deltaTime);
    st.updateAnimations(deltaTime);
    insert_2.updateAnimations(deltaTime); 
    executeFunctions(animation_queue);
    Nodes.UpdateHightLight();
    Draw();
    Nodes.TraverseCheck();

    EndMode2D();
    UI_executeFunctions();


    if(ani ==None && cur &&cur->isClicked())
    {
        isDragging = true;  
    }
    if(isDragging)
    {
        cur->SetPosition(UI::mousePos);
        Nodes.get_root()->ForwardDistanceConstraints(2*Node_radius +50);
        // Nodes.get_root()->ForwardAngleConstraints(2*PI/3);
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            isDragging = false;  
        }
    }else{ 
        UI::updateCamera();
    }
    UI::mousePos = GetMousePosition();
    DrawText("Singly Linked List", 200, 200, 40, WHITE);

    DrawText(std::to_string(deltaTime).c_str(), 500, 10, 20, WHITE);
    DrawCommonUI();
    for(int i =0 ; i<buttons.size();i++)
    {
       buttons[i]->Draw();
       buttons[i]->DrawButtonText_center();
       if(buttons[i]->IsHovered(UI::mousePos) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
       {
         buttons[i]->OnClick();
       }

    }

}
SceneManager::SceneManager()
{
    mscene = Welcome;
    scenes.push_back(new Welcome_Scene()); 
    scenes.push_back(new Menu_Scene()); 
    scenes.push_back(new Singly_Scene()); 
    scenes.push_back(new Graph_Scene());
    // scenes.push_back(new Trie_Scene());

}
SceneManager::~SceneManager() {
    for (Scene* scene : scenes) {
        delete scene;  
    }
    scenes.clear();
}
void NodeScene::DrawCommonUI()
{
    for(int i =0 ; i< Inputs.size();i++)
    {
        Inputs[i]->HandleInput(buffer,UI::mousePos);
        Inputs[i]->Draw(true);
        Inputs[i]->Send(buffer);
    }
    for(int i = 0; i<buttons.size(); i++)
    {
        buttons[i]->Draw(); 
    }
}
NodeScene::NodeScene()
{
    Inputs.push_back(new InputField(100.0f,100.0f,Vector2({0,UI::wHeight-100}),InputType::Insert));
    Inputs.push_back(new InputField(100.0f,100.0f,Vector2({0,UI::wHeight-210}),InputType::Remove));
    Inputs.push_back(new InputField(100.0f,100.0f,Vector2({0,UI::wHeight-320}),InputType::Search));
    buttons.push_back(new Button("",Vector2({0,UI::wHeight-430}),Vector2({100,100}),"Randomize"));
    buttons.push_back(new Button("",Vector2({UI::wWidth -200,UI::wHeight-430}),Vector2({100,100}),"Backward")); 
    buttons.push_back(new Button("",Vector2({UI::wWidth -200,UI::wHeight-320}),Vector2({100,100}),"Pause")); 
    buttons.push_back(new Button("",Vector2({UI::wWidth -200,UI::wHeight-210}),Vector2({100,100}),"Forward")); 
    ani_state = animation_state::Forward;
}
Singly_Scene::Singly_Scene(): NodeScene(),a(0.3,0), insert(0.5,0,20,Vector2({300,300})),d(0.5,0),isDragging(false), insert_2(1),st(1){
    Edges.clear(); 
    buttons[0]->OnClick=  [this]() {
    
        int n = std::rand() % 11 +1; 
        std::cout<<n<<"\n";
        for(int i =0 ; i <n;i++)
        {
            Vector2 pos = {static_cast<float>(std::rand() % GetScreenWidth()), static_cast<float>(std::rand() % GetScreenHeight())};
            if (pos.x + 500 < GetScreenWidth()) pos.x += 500;
            if (pos.y + 200 < GetScreenHeight()) pos.y += 200;
            if (pos.x > GetScreenWidth() - 100) pos.x -= 100;
            if (pos.y > GetScreenHeight() - 100) pos.y -= 100;
            int value = std::rand() % 1000;
            SinglyNode* insertnode = new SinglyNode(pos,Node_radius,value);
            addFunction(animation_queue,1, std::bind(&Ani_InsertRandomList ::updateTarget, &insert_2, insertnode));       
        }
        addFunction(animation_queue,0,std::bind(&Ani_Straighten::updateTarget, &st, Vector2{100,100}));
    };
    buttons[1]->OnClick=  [this]() {
       this->ani_state =  animation_state::Backward ; 
    };
    buttons[2]->OnClick=  [this]() {
        this->ani_state =  animation_state::Pause ; 
     };
     buttons[3]->OnClick=  [this]() {
        this->ani_state =  animation_state::Forward ; 
     };
}

#include <iostream>
#include <cstdlib>
#include <ctime>

std::vector<GraphNode*> Graph_Scene::graphNodes;
std::vector<Edge*>  Graph_Scene::Edges; 

Graph_Scene::Graph_Scene() : NodeScene(), created(false), ani_insert(0.3, 0, 20, {0,0}) {
    Inputs.push_back(new InputField(100.0f,100.0f,Vector2({0,UI::wHeight-540}),InputType::AddEdge));
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

Graph_Scene::~Graph_Scene() {

}   

void Graph_Scene::CheckBuffer() {
    int type;
    std::stringstream ss(buffer);
    bool inputted = false;
    ss >> type;
    inputted = true;
    switch(type)
    {
        case 0:
        {
            int value;
            ss >> value;
            Vector2 pos = {static_cast<float>(std::rand() % GetScreenWidth()), static_cast<float>(std::rand() % GetScreenHeight())};
            if (pos.x + 500 < GetScreenWidth()) pos.x += 500;
            if (pos.y + 200 < GetScreenHeight()) pos.y += 200;
            if (pos.x > GetScreenWidth() - 100) pos.x -= 100;
            if (pos.y > GetScreenHeight() - 100) pos.y -= 100;
            AddNode(pos, value);
            created = true;
        } 
        break;

        case 1: 
        {
            int value;
            ss >> value;
            // RemoveNode(value);
        }
        break;

        case 3: 
        {
            int value;
            ss >> value;
            if (findNodeByVal(value)) {
                std::cout << "Found " << value << "\n";

            }
            else std::cout << "Not found " << value << "\n";
        }
        break;

        case 4:
        {
            int fromVal, toVal, weight;
            ss >> fromVal >> toVal >> weight;
            AddEdge(fromVal, toVal, weight);
        }
        break;
    }
    if (inputted) {
        std::string newBuffer;
        std::string word;
        while (ss >> word) {
            newBuffer += word + " ";
        }
        buffer = newBuffer;
        inputted = false;
    }
}

void Graph_Scene::Draw() {
    for (const auto& node : graphNodes) {
        node->drawEdges();
    }
    for (const auto& node : graphNodes) {
        node->drawNodes();
    }
}   

void Graph_Scene::run(Scenes& mscene) {
    float deltatime = IsWindowFocused() ? GetFrameTime() : 0;
    ClearBackground(BLACK);
    DrawCommonUI();
    DrawText("Graph", 200, 200, 40, WHITE);
    CheckBuffer();
    if (IsKeyPressed(KEY_LEFT)) {
        mscene = Menu;
        created = false;
        for(int i = 0; i < Edges.size(); i++)
        {
             Edge* tmp = Edges[i];
             Edges[i] = nullptr;
             delete tmp;
        }
        Edges.clear();
        for(int i = 0; i < graphNodes.size(); i++) {
            GraphNode* tmp = graphNodes[i];
            graphNodes[i] = nullptr;
            delete tmp;
        }
        graphNodes.clear();
        return;
    }
    ani_insert.updateAnimations(deltatime);
    Draw();
}

GraphNode* Graph_Scene::findNodeByVal(int value) {
    for (auto& node : graphNodes) {
        if (node->val == value) {
            return node;
        }
    }
    return nullptr;
}

void Graph_Scene::AddNode(Vector2 position, int value) {
    ani_insert.updateTarget(value, 20, position);
}

void Graph_Scene::AddEdge(int from, int to, int weight) {
    GraphNode* fromNode = findNodeByVal(from);
    GraphNode* toNode = findNodeByVal(to);

    if (!fromNode || !toNode) {
        return;
    }
    Edges.push_back(new Edge(fromNode, toNode));
}

// void Graph_Scene::RemoveNode(int value) {
//     Edges.erase (std::remove_if())
// }

// Ani_TrieInsert Trie_Scene::i;
// TrieNodePrimary* Trie_Scene::proot = new TrieNodePrimary(Vector2{300, 300}, 20, '*');
// animation Trie_Scene::ani = None; 
// int Trie_Scene::Node_radius = 20; 
// std::vector<Edge*>Trie_Scene::edges;


// Trie_Scene::Trie_Scene(): NodeScene() {
//     edges.clear();
//     cur = proot;
// }


// void Trie_Scene:: run(Scenes& mscene){
//     if (proot->isEndOfWord)
//          std::cout<< "true" <<'\n';
//     deltaTime = IsWindowFocused() ? GetFrameTime() : 0;
//     ClearBackground(BLACK);
//     DrawCommonUI();
//     DrawText("Trie", 360, 0, 40, WHITE);
//     CheckBuffer();
    
//     if (IsKeyPressed(KEY_LEFT)) {
//         mscene = Menu;
//         for(int i =0; i<edges.size();i++)
//         {
//              Edge* tmp = edges[i];
//              edges[i] = nullptr;
//              delete tmp;
//         }
//         edges.clear();
//         cur = nullptr;
//         proot = nullptr;
//         return; 

//     };
//     i.updateAnimations(deltaTime);
//     Draw();
// }

// void Trie_Scene::Draw() {   

//     TrieNodePrimary* tmp = proot;
//     proot->Traverse(tmp);
//     for (int i = 0; i <Trie_Scene::edges.size();) {
//         if(Trie_Scene::edges[i]->Draw())
//         { 
//             i++;
//         }
//         else{
//            Trie_Scene::edges.erase(Trie_Scene::edges.begin()+i);
//         }
//     }
// }

// void Trie_Scene::CheckBuffer() {
//     int type;
//     std::stringstream ss(buffer);
//     bool inputted = false;
//     std::string key;
//     if (ani!=None) return;
//     if (ani == None) {
//         ss >> type;
//         ss >> key;
//         inputted = true;
//     }
//     std::stringstream ss1(key);
//     char x;
//     ss1 >> x;
//     switch (type) {
//         case 0: {  // Insert operation
//             if (i.getState()) {  
//                 ani = Inserting; 
//                 std::cout << "!"; 
//                 Insert(x, 1.0f); 


//             }
//         }
//         break;
        
//         case 1: {

//         }
//         break;

//         case 3: {
//             std::string x;
//             ss >> x;
//             ani = Searching;
//         }
//         break;

//     }


//     if (inputted && key.size() > 1) {
//         std::string newBuffer;
//         std::string word;
//         newBuffer += std::to_string(type);  
//         while (ss1 >> word) newBuffer += word + " ";
//         while (ss >> word) {
//             newBuffer += word + " ";
//         }
//         buffer = newBuffer;
//         inputted = false;
//     }

//     else if (inputted && key.size() == 1) {
//         std::string newBuffer;
//         std::string word;
//         cur->isEndOfWord = true;
//         cur = proot;
//         while (ss >> word) {
//             newBuffer += word + " ";
//         }
//         buffer = newBuffer;
//         inputted = false;
//     }


// }

// //main trie function
// #include <algorithm>
// void Trie_Scene::Insert(const char& word, float duration){
//     Vector2 curPos = cur->getPosition();
//     Vector2 nextPos = Vector2({curPos.x, curPos.y + 60}); 
//     TrieNodePrimary* tmp = cur;
//     if (cur->children.find(word) == cur->children.end()) {
//         TrieNodePrimary* newNode = new TrieNodePrimary(Vector2({100, 100}), 20, word);
//         std::cout << newNode->key << "\n"; 
//         Trie_Scene::i.setDuration(duration);
//         Trie_Scene::i.updateTarget(nextPos, 20, newNode);
//         bool edgeExists = std::any_of(Trie_Scene::edges.begin(), Trie_Scene::edges.end(), [tmp, newNode](Edge* edge) {
//             return edge->getFrom() == tmp && edge->getTo() == newNode;
//             });
            
//         if (!edgeExists) {
//             Trie_Scene::edges.push_back(new Edge(cur, newNode));                
//             cur->children[word] = newNode;
//         }

//     }
//     cur = cur->children[word];
//     curPos = cur->getPosition(); 
// }


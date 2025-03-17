#include "Scene.h"
#include "UI.h"
Ani_MoveList Singly_Scene::m ;
SinglyLinkedListNode Singly_Scene::Nodes = SinglyLinkedListNode();
std::vector<Edge*>Singly_Scene::Edges;
SinglyNode* Singly_Scene::cur =nullptr;
bool Singly_Scene::created = false; 
//  std::vector<Edge*>  Graph_Scene::Edges; 

animation Singly_Scene:: ani = None; 
Ani_DrawEdge Singly_Scene::de;  
std::priority_queue<std::pair<int, std::function<void()>>, 
     std::vector<std::pair<int, std::function<void()>>>, 
    FunctionComparator> Singly_Scene:: animation_queue ; 

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
void Singly_Scene::addFunction(int priority, std::function<void()> func)
{
    animation_queue.push({priority, func});
}
void Singly_Scene::executeFunctions()
{
    while (!animation_queue.empty()&& ani == None) {
        auto topFunction = animation_queue.top();
        animation_queue.pop();
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
            if(i.getState())
            {
                ss>>x; 
                addFunction(1, std::bind(&Ani_LinkedListInsert::updateTarget, &i, x, 20, insert_pos));          
           }
        }
        break;
      case 1: 
        {
            int x ;
            if(d.getState())
            {
                ss>>x; 
                addFunction(1, std::bind(&Ani_LinkedListDelete::updateTarget, &d, x));          
            }
        }
        break;
      case 3:
        { 
            if(a.getState())
            {
                int x ;
                ss>>x; 
               addFunction(1, std::bind(&Ani_LinkedListSearching::updateTarget, &a, x)); 
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
    float deltaTime = IsWindowFocused() ? GetFrameTime() : 0;
    ClearBackground(BLACK);
    DrawCommonUI();
    DrawText("Singly Linked List", 200, 200, 40, WHITE);
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
        cur = nullptr; 
        return; 

    }
    a.updateAnimations(deltaTime);
    i.updateAnimations(deltaTime); 
    m.updateAnimations(deltaTime); 
    d.updateAnimations(deltaTime);
    de.updateAnimations(deltaTime);
    
    executeFunctions();
    Nodes.UpdateHightLight();
    Draw();
    if(ani ==None && cur &&cur->isClicked())
    {
        isDragging = true;  
    }
    if(isDragging)
    {
        cur->SetPosition(UI::mousePos);
        Nodes.get_root()->ForwardDistanceConstraints(2*Node_radius +50);
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            isDragging = false;  
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
}
NodeScene::NodeScene()
{
    Inputs.push_back(new InputField(100.0f,100.0f,Vector2({0,UI::wHeight-100}),InputType::Insert));
    Inputs.push_back(new InputField(100.0f,100.0f,Vector2({0,UI::wHeight-210}),InputType::Remove));
    Inputs.push_back(new InputField(100.0f,100.0f,Vector2({0,UI::wHeight-320}),InputType::Search));
}
Singly_Scene::Singly_Scene(): NodeScene(),a(0.3,0), i(0.5,0,20,Vector2({300,300})),d(0.5,0),isDragging(false){
    Edges.clear(); 
}

#include <iostream>
Graph_Scene::Graph_Scene() : NodeScene(), curNode(nullptr), created(false) {
    Inputs.push_back(new InputField(100.0f,100.0f,Vector2({0,UI::wHeight-430}),InputType::AddEdge));
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
            Vector2 pos = UI::mousePos;
            AddNode(pos, type);
            created = true;
        } 
        break;

        case 3:
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
        graphNodes.clear();
        curNode = nullptr;
        return;
    }
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
    GraphNode* node = new GraphNode(position, value);
    graphNodes.push_back(node);
}

void Graph_Scene::AddEdge(int from, int to, int weight) {
    GraphNode* fromNode = findNodeByVal(from);
    GraphNode* toNode = findNodeByVal(to);

    if (fromNode == nullptr || toNode == nullptr) {
        std::cout << "Invalid node indices for edge: " << from << " -> " << to << std::endl;
        return;
    }
    fromNode->addEdge(toNode, weight);
}

// void Graph_Scene::RemoveNode(Vector2 position) {
//     for (auto it = graphNodes.begin(); it != graphNodes.end(); ++it) {
//         if (CheckCollisionPointCircle(position, it->getPosition(), 18)) {
//             graphNodes.erase(it);
//             break;
//         }
//     }
// }
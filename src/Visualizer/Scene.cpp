#include "Scene.h"
#include "UI.h"
#include <raymath.h>
#include <iostream>
#include "raygui.h"
bool Scene::isDarkMode = false;
bool Scene::isDefault =true;
Font Scene::currentFont=GetFontDefault();
SettingButton Scene::setting = SettingButton({1800, 20}, {80,80});
Ani_MoveList Singly_Scene::m ;
Ani_MoveNode Singly_Scene::mn(0.5);
SinglyLinkedListNode Singly_Scene::Nodes = SinglyLinkedListNode();
std::vector<Edge*>Singly_Scene::Edges;
SinglyNode* Singly_Scene::cur =nullptr;
int Singly_Scene::cur_priority =0 ;
bool Singly_Scene::created = false;
std::stack<std::pair<int, std::function<void()>>> Singly_Scene::ani_his;
std::queue<std::pair<int, std::function<void()>>>  Singly_Scene::pending_animation;

std::stack<std::pair<int, std::function<void()>>> Singly_Scene::ani_replay_his;
animation Singly_Scene:: ani = None;
animation_state Singly_Scene::ani_state = Continue;
Ani_DrawEdge Singly_Scene::de;
std::pair<int, std::function<void()>> Singly_Scene::cur_animation;
std::string NodeScene::info;
std::priority_queue<std::pair<int, std::function<void()>>, 
     std::vector<std::pair<int, std::function<void()>>>, 
    FunctionComparator> Singly_Scene:: animation_queue ; 
    std::priority_queue<std::pair<int, std::function<void()>>, 
    std::vector<std::pair<int, std::function<void()>>>, 
   FunctionComparator> Singly_Scene:: UI_animation_queue ; 
int Singly_Scene::Node_radius = 20; 

int NodeScene::maxsteps = 0 ; 
int NodeScene::stepindex = 0 ; 

std::vector<string> NodeScene:: code; 
std::vector<int> NodeScene::highlights_code;
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
void Scene::Drawbackground(){
    if (isDarkMode) {
        DrawRectangleGradientV(0, 0, GetScreenWidth(), GetScreenHeight(), dark1, dark2);
    }
    else {
        DrawRectangleGradientV(0, 0, GetScreenWidth(), GetScreenHeight(),light1, light2);
    }
}
Welcome_Scene::Welcome_Scene() {
    fontSize = 30;
    text1Pos = {200, 200};
    text2Pos = {200, static_cast<float>(GetScreenHeight()) - 200};
    sceneHeight = GetScreenHeight();
    sceneWidth = GetScreenWidth();
}
void Welcome_Scene::run(Scenes& mscene)
{
    float scaleX = GetScreenWidth() / sceneWidth;
    float scaleY = GetScreenHeight() / sceneHeight;
    ClearBackground(DARKBLUE);
    Rectangle src = { 0, 0, (float)UI::background.width, (float)UI::background.height};
    Rectangle dest = { 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()};
    DrawTexturePro(UI::background, src, dest, Vector2({0, 0}), 0.0f, WHITE);
    DrawText("DATA STRUCTURE VISUALIZATION", text1Pos.x*scaleX, text1Pos.y*scaleY, fontSize*scaleY*4/3, WHITE);
    UI::DrawFadingText(UI::time, text2Pos.x*scaleX, text2Pos.y*scaleY, fontSize*scaleY, "Press any keys to continue");
    if(GetKeyPressed()!=0)
    {
        text1Pos = {text1Pos.x*scaleX, text1Pos.y*scaleY};
        text2Pos = {text2Pos.x*scaleX, text2Pos.y*scaleY};
        fontSize = fontSize*scaleY;
        sceneWidth = GetScreenWidth();
        sceneHeight = GetScreenHeight();
        mscene = Menu;
    }
}
Menu_Scene::Menu_Scene()
{
    menuFont = 60;
    menuPos = {static_cast<float>(GetScreenWidth()) / 2 - menuFont / 2, 100};
    buttonPos = {static_cast<float>(GetScreenWidth()) / 5,  300};
    float space = buttonPos.x / 5;
    sButtons.push_back(new SceneButton("../assets/Images/SinglyLinkedList.png", Vector2({space, buttonPos.y}), Vector2({buttonPos.x, buttonPos.x}), "Singly Linked List", Singly));
    sButtons.push_back(new SceneButton("../assets/Images/Trie.png", Vector2({space * 2 + buttonPos.x, buttonPos.y}), Vector2({buttonPos.x, buttonPos.x}), "Trie", Trie));
    sButtons.push_back(new SceneButton("../assets/Images/Heap.png", Vector2({space * 3 + buttonPos.x * 2, buttonPos.y}), Vector2({buttonPos.x, buttonPos.x}), "Heap", Heap));
    sButtons.push_back(new SceneButton("../assets/Images/Graph.png", Vector2({space * 4 + buttonPos.x * 3, buttonPos.y}), Vector2({buttonPos.x, buttonPos.x}), "Graph", Graph));
    sceneHeight = GetScreenHeight();
    sceneWidth = GetScreenWidth();
    firstEntry = true;
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
    if (sceneWidth == GetScreenWidth()) firstEntry = false;
    float scaleX = GetScreenWidth() / sceneWidth;
    float scaleY = GetScreenHeight() / sceneHeight;
    float deltaTime = IsWindowFocused() ? GetFrameTime() : 0;
    ClearBackground(DARKBLUE);
    if (isDarkMode) {
        DrawRectangleGradientV(0, 0, GetScreenWidth(), GetScreenHeight(), dark1, dark2);
    }
    else {
        DrawRectangleGradientV(0, 0, GetScreenWidth(), GetScreenHeight(),light1, light2);
    }
    int textWidth = MeasureText("Menu", menuFont*scaleY);
    DrawText("Menu", GetScreenWidth() / 2 - textWidth / 2, menuPos.y*scaleY, menuFont*scaleY, WHITE);
    if (firstEntry) {
        setting.setPositionText({setting.get_position().x*scaleX, setting.get_position().y*scaleY}, {static_cast<unsigned int>(setting.get_texture().width*scaleX), static_cast<int>(setting.get_texture().height*scaleY)});
        setting.setPositionRect({setting.get_position().x, setting.get_position().y}, {setting.get_rectangle().x*scaleX, setting.get_rectangle().y*scaleY});
    }
    else {
        setting.setPositionText({setting.get_position().x*GetScreenWidth()/UI::wWidth, setting.get_position().y*GetScreenHeight()/UI::wHeight}, {static_cast<unsigned int>(setting.get_texture().width*GetScreenWidth()/UI::wWidth), static_cast<int>(setting.get_texture().height*GetScreenHeight()/UI::wHeight)});
        setting.setPositionRect({setting.get_position().x, setting.get_position().y}, {setting.get_rectangle().x*GetScreenWidth()/UI::wWidth, setting.get_rectangle().y*GetScreenHeight()/UI::wHeight});
    }
    setting.SettingDraw();
    if(setting.IsHovered(UI::mousePos) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
        mscene = Setting;
    }
    for(int i = 0; i < sButtons.size();  i++)
    {
        Vector2 pos = sButtons[i]->get_position();
        Vector2 rect = sButtons[i]->get_rectangle();
        if (firstEntry) {
            sButtons[i]->setPositionRect({pos.x*scaleX, pos.y*scaleY}, {rect.x*scaleX, rect.y*scaleY});
        }
        else {
            sButtons[i]->setPositionRect({pos.x*GetScreenWidth()/UI::wWidth, pos.y*GetScreenHeight()/UI::wHeight}, {rect.x*GetScreenWidth()/UI::wWidth, rect.y*GetScreenHeight()/UI::wHeight});
        }
        sButtons[i]->Draw();
        sButtons[i]->DrawButtonText_below(menuFont*scaleY/2);

        if(sButtons[i]->IsHovered(UI::mousePos))
        {
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                menuPos.y *= scaleY;
                menuFont *= scaleY;
                sceneWidth = GetScreenWidth();
                sceneHeight = GetScreenHeight();
                firstEntry = true;
                mscene = sButtons[i]->getButtonScenes();
            }
        }
    }
    if(IsKeyPressed(KEY_LEFT))
    {
        menuPos.y *= scaleY;
        menuFont *= scaleY;
        sceneWidth = GetScreenWidth();
        sceneHeight = GetScreenHeight();
        firstEntry = true;
        mscene = Welcome;
    }
    UI::wWidth = GetScreenWidth();
    UI::wHeight = GetScreenHeight();
    firstEntry = false;
}
#include <sstream>
void Singly_Scene::addFunction(std::priority_queue<std::pair<int, std::function<void()>>,
std::vector<std::pair<int, std::function<void()>>>,
FunctionComparator>& q,int priority, std::function<void()> func)
{
    if(priority != Singly_Scene::cur_priority  && ani != None)
    {
        pending_animation.push({priority, func});
    }else
    {
        q.push({priority, func});
    }
}
void Singly_Scene::executeFunctions(std::priority_queue<std::pair<int, std::function<void()>>,
std::vector<std::pair<int, std::function<void()>>>,
FunctionComparator>& q)
{

    if(q.empty())
    {
        cur_priority = 0 ;
        cur_animation = {0, [](){}};
        return;
    }
    while (!q.empty()) {
        auto topFunction = q.top();
        if(topFunction.first == cur_animation.first){
                q.pop();
                cur_animation = topFunction;
                topFunction.second();

        }else
        {
            if(ani == None)
            {
                q.pop();
                cur_animation = topFunction;
                scene_info_his.push(getInfo());
                topFunction.second();
            }
            else break;
        }

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
                addFunction(animation_queue,++cur_priority, std::bind(&Ani_LinkedListInsert::updateTarget, &insert, x, 20, insert_pos));
           }
        }
        break;
      case 1:
        {
            int x ;
            if(d.getState())
            {
                ss>>x;
                addFunction(animation_queue,++cur_priority, std::bind(&Ani_LinkedListDelete::updateTarget, &d, x));
            }
        }
        break;
      case 3:
        {
            if(a.getState())
            {
                int x ;
                ss>>x;
               addFunction(animation_queue,++cur_priority, std::bind(&Ani_LinkedListSearching::updateTarget, &a, x));
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
        if(Edges[i]->isDraw)Edges[i]->Draw(Edges[i]->getColor(), 0);
    }
}
void Singly_Scene::executeBackwardFunction()
{

    if(ani_his.empty() || ani != None) return;
    cur_animation = ani_his.top();
    ani_his.top().second();
    ani_his.pop();
}

Singly_Scene_Info Singly_Scene::getInfo() {
    Singly_Scene_Info info;
    std::unordered_map<SinglyNode*, SinglyNode*> oldToNew;
    SinglyNode* oldNode = Nodes.get_root();
    SinglyNode* prevNew = nullptr;
    while (oldNode) {
        SinglyNode* newNode = new SinglyNode(*oldNode);
        oldToNew[oldNode] = newNode;
        if (prevNew) {
            prevNew->SetNext(newNode);
        } else {
            info.Nodes.set_root(newNode);
        }
        prevNew = newNode;
        oldNode = oldNode->next;
    }
    info.Nodes.size = Nodes.size;
    info.cur  = cur? oldToNew[cur] : nullptr;

    for (Edge* edge : Edges) {
        SinglyNode* from = static_cast<SinglyNode*>(edge->getFrom());
        SinglyNode* to = static_cast<SinglyNode*>(edge->getTo());

        Edge* newEdge = new Edge(oldToNew[from], oldToNew[to]);
        newEdge->isDraw = edge->isDraw;
        info.Edges.push_back(newEdge);
    }
    return info;
}
void Singly_Scene::loadInfo(Singly_Scene_Info&& info) {

    std::vector<Edge*> tempEdges = std::move(info.Edges);
    SinglyLinkedListNode tempNodes = std::move(info.Nodes);

    Nodes.DeleteList();
    for (Edge* edge : Edges) {
        delete edge;
    }
    Edges.clear();

    std::unordered_map<SinglyNode*, SinglyNode*> infoToNew;
    SinglyNode* infoNode = info.Nodes.get_root();
    SinglyNode* prevNew = nullptr;

    while (infoNode) {
        SinglyNode* newNode = new SinglyNode(*infoNode);
        infoToNew[infoNode] = newNode;
        if (prevNew) {
            prevNew->SetNext(newNode);
        } else {
            Nodes.set_root(newNode);
        }
        prevNew = newNode;
        infoNode = infoNode->next;
    }
    Nodes.size = info.Nodes.size;

    for (Edge* edge : tempEdges) {
        SinglyNode* from = static_cast<SinglyNode*>(edge->getFrom());
        SinglyNode* to = static_cast<SinglyNode*>(edge->getTo());
        if (!infoToNew.count(from) || !infoToNew.count(to)) continue;
        Edge* newEdge = new Edge(infoToNew[from], infoToNew[to]);
        newEdge->isDraw = edge->isDraw;
        Edges.push_back(newEdge);
    }

    cur = Nodes.get_root();
}
void Singly_Scene::loadInfo(const Singly_Scene_Info& info) {
    Nodes.DeleteList();
    for (Edge* edge : Edges) {
        delete edge;
    }
    Edges.clear();

    std::unordered_map<SinglyNode*, SinglyNode*> infoToNew;
    SinglyNode* infoNode = info.Nodes.get_root();
    SinglyNode* prevNew = nullptr;

    while (infoNode) {
        SinglyNode* newNode = new SinglyNode(*infoNode);
        infoToNew[infoNode] = newNode;

        if (prevNew) {
            prevNew->SetNext(newNode);
        } else {
            Nodes.set_root(newNode);
        }

        prevNew = newNode;
        infoNode = infoNode->next;
    }
    Nodes.size = info.Nodes.size;
    cur  =    info.cur? infoToNew[info.cur] : info.Nodes.get_root();

    for (Edge* edge : info.Edges) {
        SinglyNode* from = static_cast<SinglyNode*>(edge->getFrom());
        SinglyNode* to = static_cast<SinglyNode*>(edge->getTo());
        if (!infoToNew.count(from) || !infoToNew.count(to)) continue;

        Edge* newEdge = new Edge(infoToNew[from], infoToNew[to]);
        newEdge->isDraw = edge->isDraw;
        Edges.push_back(newEdge);
    }

}


#include "iostream"
void Singly_Scene::Clear()
{

    while(!ani_his.empty())
    {
        ani_his.pop();
    }
    while(!animation_queue.empty())
    {
        animation_queue.pop();
    }
    while(!pending_animation.empty())
    {
        pending_animation.pop();
    }
    while(!ani_replay_his.empty())
    {
        ani_replay_his.pop();
    }
    buffer = "";
     Edges.clear();
     UI::resetCamera();
     ani = None;
     cur =nullptr;
     insert.reset();
     st.reset();
     mn.reset();
     insert_2.reset();

     while(!scene_info_his.empty())
     {
        scene_info_his.pop();
     }
     while(!scene_info_replay_his.empty())
     {
        scene_info_replay_his.pop();
     }
     Nodes.DeleteList();
     for(int i =0; i<Edges.size();i++)
         {
              Edge* tmp = Edges[i];
              Edges[i] = nullptr;
              delete tmp;
         }
}

void Singly_Scene::run(Scenes& mscene)
{

    ClearBackground(BLACK);
    Rectangle src = { 0, 0, (float)UI::background.width, (float)UI::background.height};
    Rectangle dest = { 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()};
    DrawTexturePro(UI::background, src, dest, Vector2({0, 0}), 0.0f, WHITE);

    float deltaTime = IsWindowFocused() ? GetFrameTime() : 0;
    CheckBuffer();
    if (IsKeyPressed(KEY_LEFT)) {
        mscene = Menu;
        created = false;
        Clear(); 
        sceneWidth = GetScreenWidth();
        sceneHeight = GetScreenHeight();  
        return; 
    }
    de.setDuration(0.4);
    BeginMode2D(UI::camera);
    UI::mousePos =  GetScreenToWorld2D(GetMousePosition(), UI::camera);
    Draw();

    a.updateAnimations(deltaTime);
    insert.updateAnimations(deltaTime); 

    m.updateAnimations(deltaTime);
    d.updateAnimations(deltaTime);
    de.updateAnimations(deltaTime);
    mn.updateAnimations(deltaTime);
    st.updateAnimations(deltaTime);
    insert_2.updateAnimations(deltaTime);

    if(ani == None)
    {
        while(!pending_animation.empty())
        {
            animation_queue.push(pending_animation.front());
            pending_animation.pop();
        }
    }

    executeFunctions(animation_queue);
    if(ani == None)
    {
        Nodes.UpdateHightLight();
        Nodes.TraverseCheck();
    }
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
    handle();

    for(int i =0 ; i<buttons.size();i++)
    {
       buttons[i]->Draw();
       buttons[i]->DrawButtonText_center();
       if(buttons[i]->IsHovered(UI::mousePos) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
       {
         buttons[i]->OnClick();
       }

    }
    firstEntry = false;
}
SceneManager::SceneManager()
{
    mscene = Welcome;
    scenes.push_back(new Welcome_Scene());
    scenes.push_back(new Menu_Scene());
    scenes.push_back(new Singly_Scene());
    scenes.push_back(new Graph_Scene());
    scenes.push_back(new Trie_Scene());
    scenes.push_back(new Heap_Scene());
    scenes.push_back(new Setting_Scene());
}
Setting_Scene::Setting_Scene() {
    GuiSetStyle(SLIDER,BASE_COLOR_PRESSED,ColorToInt({68,68,68,255}));
    GuiSetStyle(SLIDER,TEXT_COLOR_FOCUSED,ColorToInt({68,68,68,255}));
    GuiSetStyle(SLIDER,TEXT_COLOR_PRESSED,ColorToInt({68,68,68,255}));

    float w= GetScreenWidth();
    float h= GetScreenHeight();
    float dis = h*2/9.0f + h*4/18.0f;
    defaultFont = GetFontDefault();
    Nowester = LoadFont("../assets/Font/norwester.otf");
    sliders.push_back(new Slider({120, dis}, {(6*w/20),(h/20)}, 1));
    controls.push_back(ControlButton({120-(h/20), dis}, {h/20,h/20}, 0));
    controls.push_back(ControlButton({120+ (6*w/20), dis}, {h/20,h/20}, 1));

    sliders.push_back(new Slider({120, dis+70.0f}, {(6*w/20),(h/20)}, 2));
    controls.push_back(ControlButton({120-(h/20), dis+70.0f}, {h/20,h/20}, 0));
    controls.push_back(ControlButton({120+ (6*w/20), dis+70.0f}, {h/20,h/20}, 1));

    sliders.push_back(new Slider({120, dis+140.0f}, {(6*w/20),(h/20)}, 3));
    controls.push_back(ControlButton({120-(h/20), dis+140.0f}, {h/20,h/20}, 0));
    controls.push_back(ControlButton({120+ (6*w/20), dis+140.0f}, {h/20,h/20}, 1));

    spinners.push_back(Spinner(myfont, {120, dis+210.0f}, {(6*w/20),(h/20)}, font[0], 0));
    controls.push_back(ControlButton({120-(h/20), dis+210.0f}, {h/20,h/20}, 0));
    controls.push_back(ControlButton({120+ (6*w/20), dis+210.0f}, {h/20,h/20}, 1));

    spinners.push_back(Spinner(theme, {120, dis+280.0f}, {(6*w/20),(h/20)}, mytheme[0], 0));
    controls.push_back(ControlButton({120-(h/20), dis+280.0f}, {h/20,h/20}, 0));
    controls.push_back(ControlButton({120+ (6*w/20), dis+280.0f}, {h/20,h/20}, 1));
    block = CodeBlock({UI::wWidth/2 + 100.0f, dis}, {300, 400});

}
void Heap_Scene::CheckBuffer()
{
    cout << "CheckBuffer" << endl;
    return;
}
void Setting_Scene::run(Scenes& mscene) {

    ClearBackground({48,46,46,255});
    TextDraw();
    node->DrawNode();
    block.SetLines({
        "#include <iostream>",
        "using namespace std;",
        "int main() {",
        "    cout << \"This is a very long line that shouble be cut if the wrapline work well\" << endl;",
        "    return 0;",
        "}"
    });
    if (IsKeyDown(KEY_DOWN)) block.Scroll(5);
    if (IsKeyDown(KEY_UP)) block.Scroll(-5);
    block.Draw();
    for(int i = 0; i <sliders.size();  i++)
    {
        sliders[i]->SliderDraw();
        Vector2 textPos = sliders[i]->get_position();
        Vector2 textSize = sliders[i]->get_rectangle();
        if (i==0) {
            controls[0].ButtonDraw();
            controls[1].ButtonDraw();
            Vector2 rightPos = controls[1].get_position();
            Vector2 rightText= controls[1].get_rectangle();
            DrawTextEx(currentFont, "RED", {15, textPos.y+0.25f*textSize.y}, (float)textSize.y*0.5f, 1.0f, WHITE);
            if (controls[1].IsHovered(UI::mousePos) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) ){
                if(Slider::red<255.0f) Slider::red+=1.0f;
            }
            if (controls[0].IsHovered(UI::mousePos) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) ){
                if(Slider::red>0.0f) Slider::red-=1.0f;
            }
            node->colorNode.r = Slider::red;
            int rounded = (int)round(Slider::red);
            std::string str = std::to_string(rounded);
            const char* cstr = str.c_str();
            DrawTextEx(currentFont, cstr, {rightPos.x + rightText.x +15.0f, textPos.y+0.25f*textSize.y}, (float)textSize.y*0.5f, 1.0f, WHITE);
        }
        else if (i==1){
            controls[2].ButtonDraw();
            controls[3].ButtonDraw();
            Vector2 rightPos = controls[3].get_position();
            Vector2 rightText= controls[3].get_rectangle();
            DrawTextEx(currentFont, "GREEN", {15, textPos.y+0.25f*textSize.y}, (float)textSize.y*0.5f, 1.0f, WHITE);
            if (controls[3].IsHovered(UI::mousePos) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) ){
                if(Slider::green<255.0f) Slider::green+=1.0f;
            }
            if (controls[2].IsHovered(UI::mousePos) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) ){
                if(Slider::green>0.0f) Slider::green-=1.0f;
            }
            node->colorNode.g = Slider::green;
            int rounded = (int)round(Slider::green);
            std::string str = std::to_string(rounded);
            const char* cstr = str.c_str();
            DrawTextEx(currentFont, cstr, {rightPos.x + rightText.x +15.0f, textPos.y+0.25f*textSize.y}, (float)textSize.y*0.5f, 1.0f, WHITE);
        }
        else if (i==2){
            controls[4].ButtonDraw();
            controls[5].ButtonDraw();
            Vector2 rightPos = controls[5].get_position();
            Vector2 rightText= controls[5].get_rectangle();
            DrawTextEx(currentFont, "BLUE", {15, textPos.y+0.25f*textSize.y}, (float)textSize.y*0.5f, 1.0f, WHITE);
            if (controls[5].IsHovered(UI::mousePos) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) ){
                if(Slider::blue<255.0f) Slider::blue+=1.0f;
            }
            if (controls[4].IsHovered(UI::mousePos) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) ){
                if(Slider::blue>0.0f) Slider::blue-=1.0f;
            }
            node->colorNode.b = Slider::blue;
            int rounded = (int)round(Slider::blue);
            std::string str = std::to_string(rounded);
            const char* cstr = str.c_str();
            DrawTextEx(currentFont, cstr, {rightPos.x + rightText.x +15.0f, textPos.y+0.25f*textSize.y}, (float)textSize.y*0.5f, 1.0f, WHITE);
        }
    }

    for (int i =0; i< spinners.size(); i++){
        spinners[i].spinnerDraw();
        Vector2 textPos = spinners[i].get_position();
        Vector2 textSize = spinners[i].get_rectangle();
        if (i==0){
            controls[6].ButtonDraw();
            controls[7].ButtonDraw();
            DrawTextEx(currentFont, "FONT", {15, textPos.y+0.25f*textSize.y}, (float)textSize.y*0.5f, 1.0f, WHITE);
            if ((controls[6].IsHovered(UI::mousePos) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) )||
            (controls[7].IsHovered(UI::mousePos) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) )){
                isDefault =!isDefault;
            }
            const char* newTitle= isDefault? font[0]:font[1];
            if(!isDefault){
                currentFont=Nowester;
            }
            else currentFont= defaultFont;
            spinners[i].ChangeTitle(newTitle);
            spinners[i].DrawTextSpinner(currentFont);

        }
        else if(i==1){
            controls[8].ButtonDraw();
            controls[9].ButtonDraw();
            DrawTextEx(currentFont, "THEME", {15, textPos.y+0.25f*textSize.y}, (float)textSize.y*0.5f, 1.0f, WHITE);
            if ((controls[8].IsHovered(UI::mousePos) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) )||
            (controls[9].IsHovered(UI::mousePos) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) )){
                isDarkMode =!isDarkMode;

            }
            const char* newTitle= (!isDarkMode)? mytheme[0]:mytheme[1];
            spinners[i].ChangeTitle(newTitle);
            spinners[i].DrawTextSpinner(currentFont);
        }
    }

    if(IsKeyPressed(KEY_LEFT)){
        mscene = Menu;
    }
}

void Setting_Scene::TextDraw() {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    float spacing = 1.0f;
    if (Scene::currentFont.texture.id == 0) {
        Scene::currentFont = GetFontDefault();
    }

    // Title
    int titleFontSize = screenHeight / 9;
    const char* titleText = "SETTING";
    Vector2 titleSize = MeasureTextEx(Scene::currentFont, titleText, (float)titleFontSize, spacing);
    Vector2 titlePos = {
        (screenWidth - titleSize.x) / 2.0f,
        screenHeight / 20.0f
    };
    DrawTextEx(currentFont, titleText, titlePos, (float)titleFontSize, spacing, WHITE);
    // Section headers
    int sectionFontSize = titleFontSize / 2;
    float sectionY = titlePos.y + titleFontSize + 40;

    // DISPLAY
    const char* displayText = "DISPLAY";
    Vector2 displaySize = MeasureTextEx(currentFont, displayText, (float)sectionFontSize, spacing);
    Vector2 displayPos = {
        (screenWidth / 4.0f) - (displaySize.x / 2.0f),
        sectionY
    };
    DrawTextEx(currentFont, displayText, displayPos, (float)sectionFontSize, spacing, WHITE);

    // SOUND
    const char* soundText = "SOUND";
    Vector2 soundSize = MeasureTextEx(currentFont, soundText, (float)sectionFontSize, spacing);
    Vector2 soundPos = {
        (screenWidth * 3.0f / 4.0f) - (soundSize.x / 2.0f),
        sectionY
    };
    DrawTextEx(currentFont, soundText, soundPos, (float)sectionFontSize, spacing, WHITE);

    // Line giữa
    Vector2 start = { (float)(screenWidth / 2), sectionY };
    Vector2 end = { (float)(screenWidth / 2), (float)screenHeight };
    DrawLineEx(start, end, 2.0f, RAYWHITE);

    node = new TrieNodePrimary(Vector2{ screenWidth / 4.0f, sectionY + sectionFontSize + 40.0f }, 30.0f,'a');
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
    std::string codes; 
    for(int i = 0 ; i   < code.size();i++)
    { 
        codes += code[i]; 
    }
    drawSideBar(this->type, codes , this->highlights_code, this->info, this->progressBar,UI::getFont());
    drawButtons();
}
NodeScene::NodeScene()
{
    Inputs.push_back(new InputField(100*GetScreenWidth()/UI::wWidth,100*GetScreenHeight()/UI::wHeight,Vector2({0,(UI::wHeight-100)*GetScreenHeight()/UI::wHeight}),InputType::Insert));
    Inputs.push_back(new InputField(100*GetScreenWidth()/UI::wWidth,100*GetScreenHeight()/UI::wHeight,Vector2({0,(UI::wHeight-210)*GetScreenHeight()/UI::wHeight}),InputType::Remove));
    Inputs.push_back(new InputField(100*GetScreenWidth()/UI::wWidth,100*GetScreenHeight()/UI::wHeight,Vector2({0,(UI::wHeight-320)*GetScreenHeight()/UI::wHeight}),InputType::Search));
    buttons.push_back(new Button("",Vector2({0,(UI::wHeight-430)*GetScreenHeight()/UI::wHeight}),Vector2({100*GetScreenWidth()/UI::wWidth,100*GetScreenHeight()/UI::wHeight}),"Randomize"));
    buttons.push_back(new Button("",Vector2({(UI::wWidth -200)*GetScreenWidth()/UI::wWidth,(UI::wHeight-430)*GetScreenHeight()/UI::wHeight}),Vector2({100*GetScreenWidth()/UI::wWidth,100*GetScreenHeight()/UI::wHeight}),"Backward")); 
    buttons.push_back(new Button("",Vector2({(UI::wWidth -200)*GetScreenWidth()/UI::wWidth,(UI::wHeight-320)*GetScreenHeight()/UI::wHeight}),Vector2({100*GetScreenWidth()/UI::wWidth,100*GetScreenHeight()/UI::wHeight}),"Pause")); 
    buttons.push_back(new Button("",Vector2({(UI::wWidth -200)*GetScreenWidth()/UI::wWidth,(UI::wHeight-210)*GetScreenHeight()/UI::wHeight}),Vector2({100*GetScreenWidth()/UI::wWidth,100*GetScreenHeight()/UI::wHeight}),"Forward")); 
    isGraph = false; 
    this->progressBar = ProgressBar(UI::getFont());
    this->isCreateChosen = false;
    this->isPushChosen = false;
    this->isDeleteChosen = false;
    this->stepindex = 0;
    this->type = 0;
    this->createButton = ButtonNew({8, 415, 110, 30}, "Create", -1, BLACK, 20, UI::getFont());
    this->randomButton = ButtonNew({156.5, 449.3, 110, 30}, "Random", -1, BLACK, 20, UI::getFont());                        
    this->loadFileButton = ButtonNew({156.5, 520.6, 110, 30}, "Load File", -1, BLACK, 20, UI::getFont());                     
    this->pushButton = ButtonNew({8, 450, 110, 30}, "Insert", -1, BLACK, 20, UI::getFont());
    this->deleteButton = ButtonNew({8, 485, 110, 30}, "Delete", -1, BLACK, 20, UI::getFont());
    this->inputNumber = InputStr(156.5, 449.3, 110, 30, "", 20, UI::getFont());        
    this->playButton = ButtonNew({173, 492, 70, 30}, "Play", -1, BLACK, 20, UI::getFont());                          
    this->searchButton = ButtonNew({8, 520, 110, 30}, "Search", -1, BLACK, 20, UI::getFont());
    this->clearButton = ButtonNew({173, 562, 70, 30}, "Clear", -1, BLACK, 20, UI::getFont());                          

    this->dijkstrabutton =  ButtonNew({8, 555, 110, 30}, "Dijkstra", -1, BLACK, 20, UI::getFont());
    this->addedgeButton =  ButtonNew({8, 590, 110, 30}, "Add Edge", -1, BLACK, 20, UI::getFont());
    mRadius = 20;
}
void Singly_Scene::ClearHistory()
{
    while(!ani_his.empty())
    {
        ani_his.pop();
    }
    while(!ani_replay_his.empty())
    {
        ani_replay_his.pop();
    }

}

Singly_Scene::Singly_Scene(): NodeScene(),a(0.3,0), insert(0.5,0,20,Vector2({300,300})),d(0.5,0),isDragging(false), insert_2(1),st(1){
    sceneWidth = GetScreenWidth();
    sceneHeight = GetScreenHeight(); 
    firstEntry = true; 
    Edges.clear(); 
    buttons[0]->OnClick=  [this]() {
        ClearHistory();
        int n = std::rand() % 11 +1;
        for(int i =0 ; i <n;i++)
        {
            Vector2 pos = {static_cast<float>(std::rand() % GetScreenWidth()), static_cast<float>(std::rand() % GetScreenHeight())};
            if (pos.x + 500 < GetScreenWidth()) pos.x += 500;
            if (pos.y + 200 < GetScreenHeight()) pos.y += 200;
            if (pos.x > GetScreenWidth() - 100) pos.x -= 100;
            if (pos.y > GetScreenHeight() - 100) pos.y -= 100;
            int value = std::rand() % 1000;
            addFunction(animation_queue,++cur_priority, std::bind(&Ani_InsertRandomList ::updateTarget, &insert_2, pos,value));
        }
        addFunction(animation_queue,++cur_priority,std::bind(&Ani_Straighten::updateTarget, &st, Vector2{100,100}));
    };
    buttons[1]->OnClick=  [this]() {
        this->ani_state =  animation_state::Backward ;
    };
    buttons[2]->OnClick=  [this]() {
        if(this->ani_state ==  animation_state::Pause)
        {
            this->ani_state = Continue;
        }  else this->ani_state =  animation_state::Pause ;
     };
     buttons.push_back(new Button("",Vector2({UI::wWidth -200,UI::wHeight-650}),Vector2({100,100}),"Redo"));
    buttons.push_back(new Button("",Vector2({UI::wWidth -200,UI::wHeight-540}),Vector2({100,100}),"Undo"));

     buttons[3]->OnClick = [this]() {
        this->ani_state =  animation_state::Forward ;
     };
     buttons[4]->OnClick=  [this]() {
        if(!scene_info_replay_his.empty())
        {
            auto info = scene_info_replay_his.top();
            scene_info_his.push(info);
            scene_info_replay_his.pop();
            loadInfo(info);
        }
     };
     buttons[5]->OnClick=  [this]() {

        if(!scene_info_his.empty())
        {
         auto info = scene_info_his.top();
         scene_info_replay_his.push(info);
         scene_info_his.pop();
         loadInfo(info);
        }
     };
     buttons.push_back(new Button("",Vector2({0,UI::wHeight-540}),Vector2({100,100}),"Clear List"));
     buttons[6] ->OnClick = [this]()
     {
        if(ani ==None)
        {
            std::cout<<"A"<<"\n";
            Clear();
        }
     } ;

}

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <set>

std::vector<GraphNode*> Graph_Scene::graphNodes;
std::vector<Edge*> Graph_Scene::Edges; 
std::priority_queue<std::pair<int, GraphNode*>, std::vector<std::pair<int, GraphNode*>>, std::greater<>> Graph_Scene::pq;
std::priority_queue<std::pair<int, std::function<void()>>, 
                    std::vector<std::pair<int, std::function<void()>>>, 
                    FunctionComparator2> Graph_Scene::animation_queue;
animation Graph_Scene:: ani = None;
animation_state Graph_Scene:: ani_state = animation_state::Continue;
float MIN_DISTANCE = 100.0f;

Graph_Scene::Graph_Scene() : created(false), ani_insert(0.01, 0, 20, {0,0}), 
ani_search(1.0, 0), ani_remove(1.0), ani_dijkstra(2.0, 0),isDragging(false), draggedNode(nullptr) {
    buttons.clear();
    Inputs.clear();
    Inputs.push_back(new InputField(100, 100,Vector2({static_cast<float>(GetScreenWidth()) - 300,static_cast<float>(GetScreenHeight()) - 100}),InputType::Insert));
    Inputs.push_back(new InputField(100, 100,Vector2({static_cast<float>(GetScreenWidth()) - 300,static_cast<float>(GetScreenHeight()) - 210}),InputType::AddEdge));
    Inputs.push_back(new InputField(100, 100,Vector2({static_cast<float>(GetScreenWidth()) - 300,static_cast<float>(GetScreenHeight()) - 320}),InputType::Remove));
    Inputs.push_back(new InputField(100, 100,Vector2({static_cast<float>(GetScreenWidth()) - 300,static_cast<float>(GetScreenHeight()) - 430}),InputType::Search));
    Inputs.push_back(new InputField(100, 100,Vector2({static_cast<float>(GetScreenWidth()) - 300,static_cast<float>(GetScreenHeight()) - 540}),InputType::Randomize));
    Inputs.push_back(new InputField(100, 100,Vector2({static_cast<float>(GetScreenWidth()) - 300,static_cast<float>(GetScreenHeight()) - 650}),InputType::DijkstraRun));
    buttons.push_back(new Button("",Vector2({100, static_cast<float>(GetScreenHeight()) - 200}),Vector2({100,100}),"Clear"));
    buttons.push_back(new Button("",Vector2({static_cast<float>(GetScreenWidth())/2 - 160,static_cast<float>(GetScreenHeight()) - 200}),Vector2({100,100}),"Backward")); 
    buttons.push_back(new Button("",Vector2({static_cast<float>(GetScreenWidth())/2 - 50,static_cast<float>(GetScreenHeight()) - 200}),Vector2({100,100}),"Pause")); 
    buttons.push_back(new Button("",Vector2({static_cast<float>(GetScreenWidth())/2 + 60,static_cast<float>(GetScreenHeight()) - 200}),Vector2({100,100}),"Forward"));
    buttons.push_back(new Button("",Vector2({100, static_cast<float>(GetScreenHeight()) - 310}),Vector2({100,100}),"Load File"));
    buttons.push_back(new Button("",Vector2({static_cast<float>(GetScreenWidth())/2 - 270,static_cast<float>(GetScreenHeight()) - 200}),Vector2({100,100}),"First Step")); 
    buttons.push_back(new Button("",Vector2({static_cast<float>(GetScreenWidth())/2 + 170,static_cast<float>(GetScreenHeight()) - 200}),Vector2({100,100}),"Final Step")); 
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    isGraph = true; 
    buttons[0]->OnClick = [this]() {
        clear();
    };
    buttons[1]->OnClick = [this]() {
        this->ani_state = animation_state::Backward;
    };
    buttons[2]->OnClick = [this]() {
        if (this->ani_state == animation_state::Pause) {
            this->ani_state = animation_state::Continue;
        }
        else this->ani_state = animation_state::Pause;
    };
    buttons[3]->OnClick = [this]() {
        this->ani_state = animation_state::Forward;
    };
    buttons[4]->OnClick = [this]() {
        loadFromFile();
    };
    buttons[5]->OnClick = [this]() {
        this->ani_state = animation_state::FirstState;
    };
    buttons[6]->OnClick = [this]() {
        this->ani_state = animation_state::FinalState;
    };
    firstEntry = true;
    sceneWidth = GetScreenWidth();
    sceneHeight = GetScreenHeight();
    block = CodeBlock({1, 1}, {600, 700});
}

Graph_Scene::~Graph_Scene() {
    for (auto* edge : Edges) delete edge;
    for (auto* node : graphNodes) delete node;
    Edges.clear();
    graphNodes.clear();
    ani_dijkstra.~Ani_Dijkstra(); 
}    

void Graph_Scene::drawDescription() {
    Vector2 samplePos1 = {static_cast<float>(GetScreenWidth() - 400), 50};
    GraphNode* sample1 = new GraphNode(samplePos1, 15, 0);
    Vector2 samplePos2 = {static_cast<float>(GetScreenWidth() - 400), 100};
    GraphNode* sample2 = new GraphNode(samplePos2, 15, 0);
    DrawCircleV(samplePos1, sample1->getRadius(), sample1->colorNode);
    DrawCircleV(samplePos2, sample2->getRadius(), sample1->colorNode);
    sample1->highlight(GREEN);
    sample2->highlight(sample2->colorNode);
    DrawText("Done", samplePos1.x + 40, samplePos1.y - sample1->getRadius(), NodeScene::mRadius, WHITE);
    DrawText("Encounter", samplePos2.x + 40, samplePos2.y - sample1->getRadius(), NodeScene::mRadius    , WHITE);
    Vector2 offset = {static_cast<float>(GetScreenWidth() - 400), 150};
    DrawText("Priority Queue", offset.x, offset.y, 20, WHITE);
    while (!pq.empty()) {
        offset.y += 30;
        auto& node = pq.top();
        int w = node.first;
        int u = node.second->val;
        std::string text = "Node - " + std::to_string(u) + " - Distance: " + to_string(w);
        DrawText(text.c_str(), offset.x, offset.y, 20, WHITE);
        pq.pop();
    }
}

void Graph_Scene::run(Scenes& mscene) {
    float deltatime = IsWindowFocused() ? GetFrameTime() : 0;
    ClearBackground(BLACK);
    Drawbackground();
    DrawButtons();
    DrawText("Graph", 200, 200, 40, WHITE);
    CheckBuffer();
    if (IsKeyPressed(KEY_LEFT)) {
        mscene = Menu;
        created = false;
        clear();
        sceneWidth = GetScreenWidth();
        sceneHeight = GetScreenHeight();
        return;
    }
    BeginMode2D(UI::camera);
    UI::mousePos = GetScreenToWorld2D(GetMousePosition(), UI::camera);
    draggingNode();
    Draw();
    for (auto* node : graphNodes) {
        node->onClick();
    }
    ani_insert.updateAnimations(deltatime);
    ani_search.updateAnimations(deltatime);
    ani_remove.updateAnimations(deltatime);
    ani_dijkstra.updateAnimations(deltatime);
    EndMode2D();
    UI::mousePos = GetMousePosition();
    if (ani == DijkstraRunning) {
        drawDescription();
        block.setFontSize(30);
        block.SetLines({
            "void dijkstra(int start, const vector<vector<pair<int, int>>>& graph, vector<int>& distance) {",
            "   int n = graph.size();",
            "   distance.assign(n, INF);",
            "   distance[start] = 0;",
            "   priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;",
            "   pq.push({0, start});",
            "   while (!pq.empty()) {",
            "       auto [dist, u] = pq.top(); pq.pop();",
            "       if (dist > distance[u]) continue;",
            "       for (auto [v, weight] : graph[u]) {",
            "           if (distance[u] + weight < distance[v]) {",
            "               distance[v] = distance[u] + weight;",
            "               pq.push({distance[v], v});",
            "           }",
            "       }",
            "   }",
            "}"
        });
        if (IsKeyDown(KEY_DOWN)) block.Scroll(5);
        if (IsKeyDown(KEY_UP)) block.Scroll(-5);
        block.Draw();
    }
    executeFunctions(animation_queue);
    sceneWidth = GetScreenWidth();
    sceneHeight = GetScreenHeight();
    firstEntry = false;
}

void Graph_Scene::Draw() {
    for (const auto& node : graphNodes) node->Draw();
}

void Graph_Scene::DrawButtons() {
    for(int i =0 ; i < Inputs.size();i++)
    {
        Vector2 pos = Inputs[i]->getPosition();
        Inputs[i]->setPosition({pos.x * GetScreenWidth() / sceneWidth, pos.y * GetScreenHeight() / sceneHeight});
        Inputs[i]->HandleInput(buffer,UI::mousePos);
        Inputs[i]->Draw(true);
        Inputs[i]->Send(buffer);
    }
    for(int i = 0; i < buttons.size(); i++) {
        Vector2 pos = buttons[i]->get_position();
        buttons[i]->setPosition({pos.x * GetScreenWidth() / sceneWidth, pos.y * GetScreenHeight() / sceneHeight});
        buttons[i]->Draw();
        buttons[i]->DrawButtonText_center();
        if(buttons[i]->IsHovered(UI::mousePos) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            buttons[i]->OnClick();
        }
    }
}

void Graph_Scene::CheckBuffer() {
    int type;
    std::stringstream ss(buffer);
    bool inputted = false;
    if (ani == None) {
        ss >> type;
        inputted = true;
    }
    switch(type)
    {
        case 0: {
            int value; ss >> value;
            GraphNode* f = findNodeByVal(value);
            if (!f && ani_insert.getState()) {
                AddNode(value);
            }
            else if (f) {
                std::cout << "Value " << value << " has already been existed in Graph\n";
            }
        }
        break;

        case 1:
        {
            int value;
            bool searched = false;
            if (ss >> value && ani_search.getState()) {
                ani_search = Ani_GraphSearch(1.0, value);
                GraphNode* startNode = graphNodes.empty() ? nullptr : graphNodes[0];
                if (startNode) {
                    searched = true;
                    addFunction(animation_queue, 1, std::bind(&Ani_GraphSearch::updateTarget, &ani_search, startNode));
                }
                else {
                    std::cout << "Graph is empty, cannot remove\n";
                }
            }
            if (searched) {
                GraphNode* removeNode = findNodeByVal(value);
                std::cout << removeNode->val << "\n";
                if (removeNode && ani_remove.getState()) {
                    ani_remove = Ani_GraphRemove(1.0);
                    addFunction(animation_queue, 0, std::bind(&Ani_GraphRemove::updateTarget, &ani_remove, removeNode));
                }
            }
        } break;

        case 3:
        {
            int value;
            if (ss >> value && ani_search.getState()) {
                ani_search = Ani_GraphSearch(1.0, value);
                GraphNode* startNode = graphNodes.empty() ? nullptr : graphNodes[0];
                if (startNode) {
                    addFunction(animation_queue, 1, std::bind(&Ani_GraphSearch::updateTarget, &ani_search, startNode));

                }
                else {
                    std::cout << "Graph is empty, cannot search\n";
                }
            }

        } break;

        case 4:
        {
            int fromVal, toVal, weight;
            ss >> fromVal >> toVal >> weight;
            AddEdge(fromVal, toVal, weight);
        } break;

        case 5:
        {
            int nums;
            if (ss >> nums) randomize(nums);
        } break;

        case 6:
        {
            int src;
            if (ss >> src) {
                for (auto& node : graphNodes) {
                    if (node->val == src && ani_dijkstra.getState()) {
                        ani_dijkstra = Ani_Dijkstra(2.0, graphNodes.size());
                        ani_dijkstra.updateTarget(node);
                        break;
                    }
                }
            }
        } break;
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

GraphNode* Graph_Scene::findNodeByVal(int value) {
    for (auto* node : graphNodes) {
        if (node->val == value) return node;
    }
    return nullptr;
}

void generatePos(Vector2& pos, vector<GraphNode*>& graph) {
    bool tooClose;
    int attempts = 0;
    do {
        tooClose = false;
        // Place nodes within the rectangular boundaries
        pos = {static_cast<float>(GetRandomValue(300, GetScreenWidth() - 300)), static_cast<float>(GetRandomValue(0, GetScreenHeight() - 200))};

        // Check for overlap with existing nodes
        for (const auto* node : graph) {
            Vector2 existingPos = node->getPosition();
            float dist = sqrt(pow(pos.x - existingPos.x, 2) + pow(pos.y - existingPos.y, 2));
            if (dist < MIN_DISTANCE) {
                tooClose = true;
                break;
            }
        }
        attempts++;
    } while (tooClose && attempts < 1000); // Limit attempts to avoid infinite loop

    if (attempts >= 1000) {
        std::cout << "Warning: Could not find a non-overlapping position after 100 attempts\n";
        return;
    }
}

void Graph_Scene::AddNode(int value) {
    Vector2 pos;
    generatePos(pos, graphNodes);
    std::cout << "Adding node " << value << " at (" << pos.x << ", " << pos.y << ")\n";
    GraphNode* newNode = new GraphNode(GetScreenToWorld2D(pos, UI::camera), NodeScene::mRadius, value);
    addFunction(animation_queue, 1, std::bind(&Ani_GraphInsert::updateTarget, &ani_insert, newNode));
    created = true;
}

void Graph_Scene::AddEdge(int from, int to, int weight) {
    if (ani == None) {
        ani = EdgeDrawing;
        GraphNode* fromNode = findNodeByVal(from);
        GraphNode* toNode = findNodeByVal(to);
        if (fromNode && toNode) {
            auto& adj = fromNode->getAdj();
            if (std::find(adj.begin(), adj.end(), toNode) == adj.end()) {
                fromNode->makeAdjacent(toNode);
                toNode->makeAdjacent(fromNode);
                Edge* newEdge = new Edge(fromNode, toNode);
                newEdge->weight = weight;
                Edges.push_back(newEdge);
                std::cout << "Edge added: " << from << " -> " << to << " (weight: " << weight << ")\n";
            }
            else {
                std::cout << "Edge already exists: " << from << " -> " << to << "\n";
            }
        }
        else {
            std::cout << "Failed to add edge: Node " << (fromNode ? to : from) << " not found\n";
        }
        ani = None;
    }
}

void Graph_Scene::randomize(int nodes) {
    clear();
    std::vector<GraphNode*> tempGraph;
    unordered_set<int> valSet;
    for (int i = 0; i < nodes; i++) {
        Vector2 pos;
        generatePos(pos, tempGraph);
        int value;
        do {
            value = std::rand() % 100;
        } while (valSet.find(value) != valSet.end());
        std::cout << "Adding node " << value << " at (" << pos.x << ", " << pos.y << ")\n";
        GraphNode* newNode = new GraphNode(GetScreenToWorld2D(pos, UI::camera), NodeScene::mRadius, value);
        tempGraph.push_back(newNode);
        valSet.insert(value);
        addFunction(animation_queue, 1, std::bind(&Ani_GraphInsert::updateTarget, &ani_insert, newNode));
    }
    created = true;

    // Add Edges
    int minEdges = nodes - 1;
    int maxPossibleEdges = (nodes * (nodes - 1)) / 2;
    int maxEdges = std::min(maxPossibleEdges, 3 * minEdges);
    int numEdges = (minEdges < maxEdges) ? (std::rand() % (maxEdges - minEdges + 1) + minEdges) : minEdges;
    std::cout << "Generating " << numEdges << " edges (range: " << minEdges << " to " << maxEdges << ")\n";
    int edgeCount = 0;
    while (edgeCount < numEdges && tempGraph.size() >= 2) {
        int fromIdx = std::rand() % tempGraph.size();
        int toIdx = std::rand() % tempGraph.size();
        if (fromIdx != toIdx) {
            int weight = std::rand() % 50;
            std::cout << "Queuing edge: " << tempGraph[fromIdx]->val << " -> " << tempGraph[toIdx]->val << " (weight: " << weight << ")\n";
            addFunction(animation_queue, 0, std::bind(&Graph_Scene::AddEdge, this, tempGraph[fromIdx]->val, tempGraph[toIdx]->val, weight));
            edgeCount++;
        }
    }

    tempGraph.clear();
}

void Graph_Scene::clear() {
    for (auto* edge : Edges) delete edge;
    for (auto* node : graphNodes) delete node;
    Edges.clear();
    graphNodes.clear();
    delete draggedNode;
    ani = None;
    ani_insert.setState(true);
    ani_search.setState(true);
    ani_remove.setState(true);
    ani_dijkstra.setState(true);
}

void Graph_Scene::loadFromFile() {
    const char* filter[] = {"*.txt"};
    const char* filePath = tinyfd_openFileDialog(
        "Select a text file", // Title
        "", // Default path (empty = open from last used folder)
        1, // Number of filter patterns
        filter, // Filter patterns
        "Text file (*.txt)", // Filter description
        0 // Single file seclection mode
    );

    if (filePath) {
        std::cout << "Trying to open file " << filePath << "\n";
        std::ifstream fin(filePath);
        if (fin.is_open()) {
            clear();
            int nodeNums = 0;
            if (fin >> nodeNums) {
                for (int i = 0; i < nodeNums; i++) {
                    int value;
                    if (fin >> value) {
                        std::cout << value << "\n";
                        AddNode(value);
                    }
                }
            }
            else std::cerr << "Error: Can not fin numnodes\n";
            int edgeNums = 0;
            if (fin >> edgeNums) {
                for (int i = 0; i < edgeNums; i++) {
                    int u, v, w;
                    if (fin >> u >> v >> w) {
                        std:: cout << u << " " << v << " " << w << "\n";
                        addFunction(animation_queue, 0, std::bind(&Graph_Scene::AddEdge, this, u, v, w));
                    }
                }
            }
            else std::cerr << "Error: Can not fin numedges\n";
        }
        else std::cerr << "Error: Can not open file\n";
        fin.close();
    }
}

void Graph_Scene::draggingNode() {
    if (!isDragging) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mousePos = GetScreenToWorld2D(GetMousePosition(), UI::camera);
            for (auto* node : graphNodes) {
                if (CheckCollisionPointCircle(mousePos, node->getPosition(), node->getRadius())) {
                    isDragging = true;
                    draggedNode = node;
                    break;
                }
            }
        }
        else {
            UI::updateCamera();
        }
    }
    if (isDragging && draggedNode) {
        Vector2 mousePos = GetScreenToWorld2D(GetMousePosition(), UI::camera);
        draggedNode->setPosition(mousePos);

        draggedNode->repulseNearbyNodes(MIN_DISTANCE);

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            isDragging = false;
            draggedNode = nullptr;
        }
    }
}

void Graph_Scene::addFunction(std::priority_queue<std::pair<int, std::function<void()>>,
                std::vector<std::pair<int, std::function<void()>>>,
                FunctionComparator2>& q, int priority, std::function<void()> func) {
    q.push({priority, func});
    std::cout << "Push function with priority " << priority << "\n";
}

void Graph_Scene::executeFunctions(std::priority_queue<std::pair<int, std::function<void()>>,
                                std::vector<std::pair<int, std::function<void()>>>,
                                FunctionComparator2>& q) {
    while (!q.empty() && ani == None) {
        auto topFunc = q.top();
        if ((!ani_insert.getState() && topFunc.first == 0) || (!ani_search.getState() && topFunc.first == 0)) break;
        q.pop();
        topFunc.second();
        std::cout << "Executed function with priority " << topFunc.first << "\n";
    }
}

Ani_TrieInsert Trie_Scene::i;
TrieNodePrimary* Trie_Scene::proot = new TrieNodePrimary(Vector2{0, -300}, 30, '*');
animation Trie_Scene::ani = None;
animation_state Trie_Scene::state = Pause;
animation_state Trie_Scene::ani_state = Pause;
int Trie_Scene::Node_radius = 30;
std::vector<Edge*>Trie_Scene::edges;

bool candelete = false;

Trie_Scene::Trie_Scene(): NodeScene() {
    edges.clear();
    levelMap[100] = {proot};
    cur = proot;
    balancePointer = cur;
    pushed=false;
    firstDelete= true;
    static bool seeded = false;
        if (!seeded) {
            seeded = true;
        }
    buttons[0]->OnClick=  [this]() {

        std::string result = "";
        for (int i = 0; i < 5; ++i) {
            char c = 'a' + rand() % 26;
            result += c;
        }
        buffer += "0 ";
        buffer+= result + " ";

    };
    buttons[1]->OnClick=  [this]() {

        if (ani_state==Backward) {
            this->ani_state = animation_state::Pause;
         }
         else {this->ani_state =  animation_state::Backward ; }
    };
    buttons[2]->OnClick=  [this]() {
        if(this->state ==  animation_state::Pause)
        {
            this->state = Continue;
            buttons[2]->SetText("Continue");
        }  else {
            this->state =  animation_state::Pause ;
            buttons[2]->SetText("Pause");
        }


     };
     buttons.push_back(new Button("",Vector2({UI::wWidth -200,UI::wHeight-650}),Vector2({100,100}),"Redo"));
    buttons.push_back(new Button("",Vector2({UI::wWidth -200,UI::wHeight-540}),Vector2({100,100}),"Undo"));
    buttons.push_back(new Button("",Vector2({100,UI::wHeight-430}),Vector2({100,100}),"Load File"));

     buttons[3]->OnClick = [this]() {
        if (ani_state==Forward) {
            this->ani_state = animation_state::Pause;
         }
         else {this->ani_state =  animation_state::Forward ; }

     };
     buttons[4]->OnClick=  [this]() {
        if(ani==None)
            this->ani_state= animation_state::Redo;
     };
     buttons[5]->OnClick=  [this]() {
        if(ani==None)
            this->ani_state= animation_state::Undo;
     };
     buttons[6]->OnClick = [this]() {
        loadFromFile();
    };
    buttons.push_back (new Button("",Vector2({0,UI::wHeight-390}),Vector2({100,100}),"Clear"));
    buttons[7]->OnClick = [this]() {
        clear();
    };

}

// void Trie_Scene:: run(Scenes& mscene){

//     deltaTime = IsWindowFocused() ? GetFrameTime() : 0;
//     Color Theme = {30,30,30,225};
//     ClearBackground(Theme);
//     Drawbackground();
//     DrawCommonUI();
//     DrawText("Trie", 1000, 0, 40, WHITE);
//     CheckBuffer();
//     if (ani ==None){
//         deleteNode();
//     }
//     if (IsKeyPressed(KEY_LEFT)) {
//         mscene = Menu;
//         for(int i =0; i<edges.size();i++)
//         {
//             Edge* tmp = edges[i];
//             edges[i] = nullptr;
//             delete tmp;
//         }
//         edges.clear();
//         return;

//     };
//     i.updateAnimations(deltaTime);
//     s.updateAnimations(deltaTime);
//     d.updateAnimations(deltaTime);
//     if ( (ani == Updating) ) {
//         std::cout << "Begin balance" << "\n";
//         if (cur!= proot) balance (cur->getPosition().y);
//         else {
//             balance(balancePointer->getPosition().y);
//             balancePointer = cur;
//         }
//     }
//     updateHelper();
//     Draw();
// }
void Trie_Scene::run(Scenes& mscene) {
    deltaTime = IsWindowFocused() ? GetFrameTime() : 0;
    Color Theme = {30, 30, 30, 225};
    ClearBackground(Theme);

    // UI phía ngoài camera (nền, tiêu đề, menu)
    Drawbackground();
    DrawCommonUI();
    //
    //printBalance(proot->getPosition().y);

    for(int i =0 ; i<buttons.size();i++)
    {
       buttons[i]->Draw();
       buttons[i]->DrawButtonText_center();
       if(buttons[i]->IsHovered(UI::mousePos) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
       {
         buttons[i]->OnClick();
       }

    }
    DrawText("Trie", 1000, 0, 40, WHITE);

    CheckBuffer();
    
    if (ani == None) {
        UndoTrie();
        RedoTrie();
    }

    // Quay lại menu
    if (IsKeyPressed(KEY_LEFT)) {
        mscene = Menu;
        for (int i = 0; i < edges.size(); i++) {
            Edge* tmp = edges[i];
            edges[i] = nullptr;
            delete tmp;
        }
        edges.clear();
        UI::resetCamera();
        return;
    }

    // ====== CAMERA ZONE ======
    BeginMode2D(UI::camera);

    // Cập nhật vị trí chuột theo thế giới thực (sau khi phóng to/thu nhỏ)
    UI::mousePos = GetScreenToWorld2D(GetMousePosition(), UI::camera);

    // Cập nhật và xử lý các animation
    i.updateAnimations(deltaTime);
    s.updateAnimations(deltaTime);
    d.updateAnimations(deltaTime);

    if (ani == Updating) {
        //std::cout << "Begin balance" << "\n";
        if (cur != proot) balance(cur->getPosition().y);
        else {
            balance(balancePointer->getPosition().y);
            balancePointer = cur;
        }
    }

    updateHelper();
    Draw(); // vẽ các node, edge,...

    EndMode2D();
    UI::updateCamera();
    // Cập nhật lại UI::mousePos thành vị trí thật để dùng cho các UI khác
    UI::mousePos = GetMousePosition();
}

void Trie_Scene::Draw() {
    TrieNodePrimary* tmp = proot;
    proot->Traverse(tmp);
    for (int i = 0; i <Trie_Scene::edges.size();) {
        if(Trie_Scene::edges[i]->TrieDraw())
       {
            i++;
        }
        else{
            std::cout << "Error in drawing edge!" <<"\n";
           Trie_Scene::edges.erase(Trie_Scene::edges.begin()+i);
        }
    }

}

void Trie_Scene::CheckBuffer() {
    int type;
    std::stringstream ss(buffer);
    bool inputted = false;
    bool notFound = false;
    bool highLight= false;

    std::string key;
    if (ani!=None || state == Pause) return;
    if (ani == None && state==Continue) {
        ss >> type;
        ss >> key;
        inputted = true;
    }
    if(!pushed && !buffer.empty() && type!=3){
        std::pair <InputType, std::string> current;
        current = std::make_pair(static_cast<InputType>(type), key);
        std::cout<<"Pushing"<< current.first<<" "<< current.second<<"\n";
        history.push(current);
        pushed=true;
        if (ani_state!=Forward || ani_state!=Backward )  ani_state=Pause;
    }

    std::stringstream ss1(key);
    switch (type) {
        case 0: {
            if (i.getState()) {
                char x;
                ss1 >> x;
                ani = Inserting;
                //std::cout << "!";
                //std :: cout << x <<"\n";
                Insert(x, 1.0f);
                if (key.size()==1){
                    highLight=true;
                }
            }

        }
        break;

        case 1: {
            ani = Removing;
            if (ani_state==Backward || ani_state== Forward){

                std::string x;
                ss1 >> x;
                bool removed=removeWord(proot, x,0);
                if (removed){
                    d.setDuration(1.0f);
                    d.play();
                }
                else{
                    d.setDuration(1.0f);
                    d.play();
                }
                notFound=true;
                pushed =false;
            }
            else {
                char x;
                ss1 >> x;
                if (firstDelete){
                    removeWordStep(proot, key, 0);
                }
                helpDeleteStep(x, 0.8f);
                d.play();

            }
        }
        break;

        case 2: {


        }
        break;

        case 3: {
            char x;
            ss1 >> x;
            ani = Searching;
            bool search = Search(x, 1.3f);
            if (search && key.size() ==1 && cur->isEndOfWord){
                s.setKey(wordSearch);
                s.setDone(true);
                cur =proot;
                std::cout<<"case 1"<<"\n";
            }
            else if (!search && key.size()>1){
                s.setKey(wordSearch);
                s.setDone(true);
                cur = proot;
                notFound=true;
                s.setDuration(1.0f);
                s.play();
                std::cout<<"case 2"<<"\n";
            }
            else if(search && key.size() ==1 && !cur->isEndOfWord){
                s.setKey(wordSearch);
                s.setDone(true);
                cur =proot;
                std::cout<<"case 3"<<"\n";
            }
        }
        break;

    }

    if (inputted && key.size() > 1) {
        std::string newBuffer;
        std::string word;
        if (!notFound){
            newBuffer += std::to_string(type);
            while (ss1 >> word) newBuffer += word + " ";
        }
        while (ss >> word) {
            newBuffer += word + " ";
        }
        buffer = newBuffer;
        inputted = false;
        return;
    }

    else if (inputted && key.size() == 1) {
        std::string newBuffer;
        std::string word;
        cur->isEndOfWord = true;
        if(highLight){
            cur->SetPrimaryHighLight();
            highLight=false;
        }
        balancePointer = cur;
        cur = proot;
        while (ss >> word) {
            newBuffer += word + " ";
        }
        //if (ani_state==Backward||ani_state==Forward) ani_state=Pause;
        buffer = newBuffer;
        inputted = false;
        pushed= false;
        firstDelete = true;
        return;
    }

}

//main trie function
#include <algorithm>
void Trie_Scene::Insert(const char& word, float duration){
   Vector2 curPos = cur->getPosition();
    int level = curPos.y + 80;
    int index;
    Vector2 nextPos;
    TrieNodePrimary* tmp = cur;

    if (cur->children.find(word) == cur->children.end()) {
        TrieNodePrimary* newNode = new TrieNodePrimary(Vector2({curPos.x-300, curPos.y-200}), 30, word);
        index = calculateIndex(level, word);
        levelMap[level].insert(levelMap[level].begin()+index, newNode);
        std::cout << newNode->key << "\n";
        cur->children[word] = newNode;
        nextPos = calculatePosition(level, index);
        Trie_Scene::i.setDuration(duration);
        Trie_Scene::i.updateTarget(nextPos, 30, newNode);
        bool edgeExists = std::any_of(Trie_Scene::edges.begin(), Trie_Scene::edges.end(), [tmp, newNode](Edge* edge){
            return (edge->getFrom() == tmp) && (edge->getTo() == newNode);
            });
        if (!edgeExists) {
            Trie_Scene::edges.push_back(new Edge(cur, newNode));
        }

    }
    else if (cur->children.find(word) != cur->children.end()){
        ani = None;
    }
    cur = cur->children[word];
    //curPos = cur->getPosition();

}

bool Trie_Scene::Search(char c, float duration) {
    TrieNodePrimary* tmp = cur;
    bool found = true;
    wordSearch += c;
    std::cout << "search for "<<c<<"\n";
    if (tmp->children.find(c) != tmp->children.end()) {
        tmp = tmp->children[c];
        tmp->SetPrimaryHighLight();
        s.setDuration(duration);
        s.play();
        std::cout << "found "<<c<<"\n";
    }
    else {
        found = false;
    }
    cur=tmp;
    return found ;
}
bool Trie_Scene::removeWordStep(TrieNodePrimary* node, const string& word, int depth){
    if (!node) return false;


    if (depth == word.size()) {
        if (!node->isEndOfWord) return false;
        node->isEndOfWord = false;
        node->SetNullHighLight();
        node->deleting=true;
        return node->children.empty();
    }

    char ch = word[depth];

    // Kiểm tra ch có tồn tại không trước khi truy cập
    if (node->children.find(ch) == node->children.end()) return false;

    if (removeWordStep(node->children[ch], word, depth + 1)) {
        TrieNodePrimary* tmp = node->children[ch];
        TrieNodePrimary* tmp1 = node;
        

        if (node->children[ch]) {
           deleteQueue.push(node->children[ch]);
           node->children[ch]->deleting=true;
           deleteQueue.push(node);
        }
        else std::cout << "Error!" << "\n";

        if((node->canDelete(tmp1)|| node->children.empty()) && !node->isEndOfWord ) {
            std::cout<< "Deleting node " << tmp->key<< "\n";
            return true;}
        else {
            return false;
        }
    }
    firstDelete = false;
    return false;

}
void Trie_Scene::helpDeleteStep(const char c, float duration) {
    //std::cout << "Running helpDeleteStep...\n";
    //std::cout << "deleteQueue size: " << deleteQueue.size() << "\n";

    if (deleteQueue.size() >= 2) {
        TrieNodePrimary* tmp = deleteQueue.front();
        deleteQueue.pop();
        TrieNodePrimary* parent = deleteQueue.front();
        deleteQueue.pop();

        if (tmp) {
            int level = tmp->getPosition().y;

            // Xóa các cạnh
            Trie_Scene::edges.erase(
                std::remove_if(Trie_Scene::edges.begin(), Trie_Scene::edges.end(), [tmp](Edge* edge) {
                    if (edge->getFrom() == tmp || edge->getTo() == tmp) {
                        delete edge;
                        return true;
                    }
                    return false;
                }),
                Trie_Scene::edges.end()
            );

            // Xóa node trong levelMap
            if (levelMap.find(level) != levelMap.end()) {
                auto& vec = levelMap[level];
                vec.erase(std::remove(vec.begin(), vec.end(), tmp), vec.end());
                if (vec.empty()) levelMap.erase(level);
            }
            
            std::cout << "Deleted node: " << tmp->key << "\n";
            char ch = tmp->key;
            parent->children.erase(ch);
            
            //delete tmp;
            d.setDuration(duration);
         }
    // else {
    //         std::cout << "tmp is NULL\n";
    //     }
    // } else {
    //     std::cout << "Not enough elements in deleteQueue.\n";
    // }
}
}

//void Trie_Scene::findParent(TrieNodePrimary* node){}

bool Trie_Scene::removeWord(TrieNodePrimary* node, const string& word, int depth) {
    if (!node) return false;


    if (depth == word.size()) {
        if (!node->isEndOfWord) return false;
        node->isEndOfWord = false;
        return node->children.empty();
    }

    char ch = word[depth];

    // Kiểm tra ch có tồn tại không trước khi truy cập
    if (node->children.find(ch) == node->children.end()) return false;

    if (removeWord(node->children[ch], word, depth + 1)) {
        TrieNodePrimary* tmp = node->children[ch];
        if (tmp) {  // Kiểm tra tmp != nullptr trước khi thao tác
            int level = tmp->getPosition().y; // Lưu level trước khi xóa

            Trie_Scene::edges.erase(
                std::remove_if(Trie_Scene::edges.begin(), Trie_Scene::edges.end(), [tmp](Edge* edge) {
                    if (edge->getFrom() == tmp || edge->getTo() == tmp) {
                        delete edge;
                        return true;
                    }
                    return false;
                }),
                Trie_Scene::edges.end()
            );
            for (auto edge : Trie_Scene::edges) {
               if (edge->getFrom() == tmp || edge->getTo() == tmp) {
                    std::cout << "error!" << "\n";
                }
            }

            if (levelMap.find(level) != levelMap.end()) {
                auto& vec = levelMap[level];

                vec.erase(
                    std::remove(vec.begin(), vec.end(), tmp),
                    vec.end()
                );

                if (vec.empty()) {
                    levelMap.erase(level);
                }
            }
            bool stillExists = isTmpPresent(tmp);
           // std::cout << "tmp still in levelMap: " << (stillExists ? "YES" : "NO") << "\n";

        }

        if (node->children[ch]) {
           // std::cout <<"before delete"<<"\n";
            deleteAll.push(node->children[ch]);
            //std::cout <<"deleted"<<"\n";
            node->children.erase(ch);   // Xóa khỏi danh sách children
        }
        else std::cout << "Error!" << "\n";

        if(!node->isEndOfWord && node->children.empty()) return true;
        else {
            return false;
        }
    }
    return false;
}

void Trie_Scene::deleteNode(){

    if(!deleteQueue.empty()){
        std::cout << "Deleting"<< "\n";
        TrieNodePrimary* tmp = deleteQueue.front();
        // for (auto edge : Trie_Scene::edges) {
        //     if (edge->getFrom() == tmp|| edge->getTo() == tmp) {
        //         std::cout << "Edge Error!\n";
        //         return;
        //     }
        // }
        // std::cout << "Edge None Error!\n";
        deleteQueue.pop();
        std::cout<<tmp->key<<" before delete (queue)"<<"\n";
        delete tmp;
        std::cout<<" after delete"<<"\n";
    }

}
bool Trie_Scene::isTmpPresent(TrieNodePrimary* tmp) {
    for (const auto& [key, vec] : levelMap) {
        if (std::find(vec.begin(), vec.end(), tmp) != vec.end()) {
            return true; // Tìm thấy tmp trong một vector nào đó
        }
    }
    return false; // Không tìm thấy tmp ở bất kỳ đâu
}
void Trie_Scene::printBalance(int level){
    int lev= level;
    while (levelMap.find(lev) != levelMap.end() && !levelMap[lev].empty()){
        for (TrieNodePrimary* parent : levelMap[lev]){
            std::cout<< "Node in level "<< lev << " : "<< parent->key;
        }
        std::cout<<"\n";
        lev= lev+80;
    }
}
// Function to balance nodes
void Trie_Scene:: balance(int level){
    int lev = level;
    int print =0;
    while (levelMap.find(lev) != levelMap.end() && !levelMap[lev].empty()){
        for (TrieNodePrimary* parent : levelMap[lev]){
            if (parent->children.empty()) continue;
            Vector2 parentPosition = parent->getPosition();
            int posX= parentPosition.x;
           int sumofChildren = 0;
            for(auto& pair:parent->children){
                Vector2 childPosition = pair.second->getPosition();
                sumofChildren+=childPosition.x;
            }
            int oldPosition = sumofChildren/parent->children.size();
            int offset = posX - oldPosition;
            for(auto& pair:parent->children){
                Vector2 childPosition = pair.second->getPosition();
                pair.second->SetPosition({childPosition.x + offset,childPosition.y});
            }

        }
        checkBalance(lev);
        lev += 80;
    }
    //std::cout << "Done first half"<<"\n";
    lev = level - 80;
    while (levelMap.find(lev) != levelMap.end() && !levelMap[lev].empty()){
        for (TrieNodePrimary* parent : levelMap[lev]){
            if (parent->children.empty()) continue;
            Vector2 parentPosition = parent->getPosition();
           int posX= parentPosition.x;
            int sumofChildren = 0;
            for(auto& pair:parent->children){
                Vector2 childPosition = pair.second->getPosition();
                sumofChildren+=childPosition.x;
            }
            int oldPosition = sumofChildren/parent->children.size();
            int offset = posX - oldPosition;
            parent->SetPosition({parentPosition.x - offset, parentPosition.y});
        }
        checkBalance(lev);
        lev -= 80;
    }
    //std::cout << "Done balancing"<<"\n";
    ani =  None;
}


void Trie_Scene::checkBalance(int level) {
    if (levelMap[level].empty()) return;

    int n = levelMap[level].size();

    for (int i = 0; i < n; i++) {
        TrieNodePrimary* tmp = levelMap[level][i];
        Vector2 pos = tmp->getPosition();

        // Left neighbor
        if (i > 0) {
            Vector2 neighbor = levelMap[level][i - 1]->getPosition();
            if (pos.x <= neighbor.x + 80.0f) {
                float offset = 80.0f - (pos.x - neighbor.x);
                for (int j = i - 1; j >= 0; j--) {
                    Vector2 curPos = levelMap[level][j]->getPosition();
                    levelMap[level][j]->SetPosition({curPos.x - offset, curPos.y});
                }
            }
        }

        // Right neighbor
        if (i < n - 1) {
            Vector2 neighbor = levelMap[level][i + 1]->getPosition();
            if (pos.x + 80.0f >= neighbor.x) {
                float offset = 80.0f - (neighbor.x - pos.x);
                for (int j = i + 1; j < n; j++) {
                    Vector2 curPos = levelMap[level][j]->getPosition();
                    levelMap[level][j]->SetPosition({curPos.x + offset, curPos.y});
                }

            }
        }
    }
}

Vector2 Trie_Scene::calculatePosition(int level, int index){
    if (levelMap[level].empty()) return{0,0};


   if ((levelMap[level].size()==1) || (cur->children.size()==1))  {
        Vector2 parent = cur->getPosition();
        Vector2 newPosition = {parent.x, parent.y+80};
        //std:: cout << "Right Level " <<level <<" "<< " new pos " << newPosition.x << " " << newPosition.y << "\n";
        return newPosition;
   }
    else {
       float distance = 80 / (levelMap[level].size()-1);
        for (int i =0; i <levelMap[level].size(); i++ ){
            TrieNodePrimary* tmp = levelMap[level][i];
            if (i<index) {
                Vector2 old = tmp->getPosition();
                //std:: cout << "Level " <<level <<" "<< tmp->key << " old pos " << old.x << " " << old.y << "\n";
                Vector2 newPosition = {old.x-distance, old.y};
                //std:: cout << "Level " <<level <<" "<< tmp->key << " new pos " << newPosition.x << " " << newPosition.y<< "\n";
                tmp->SetPosition(newPosition);
            }
            if (i> index){
                Vector2 old = tmp->getPosition();
                //std:: cout << "Level " <<level <<" "<< tmp->key << "old pos " << old.x << " " << old.y << "\n";
                Vector2 newPosition = {old.x+ distance, old.y};
                //std:: cout << "Level " <<level <<" "<< tmp->key << " new pos " << newPosition.x << " " << newPosition.y<< "\n";
                tmp->SetPosition(newPosition);
            }

        }
        if (index > 0 && index < levelMap[level].size() - 1) {
            Vector2 neighbor1 = levelMap[level][index-1]->getPosition();
            Vector2 neighbor2 = levelMap[level][index+1]->getPosition();
            Vector2 newPosition = {(neighbor1.x + neighbor2.x)/2, neighbor1.y};
            return newPosition;
        }

        else if (index > 0 && index == levelMap[level].size() - 1){
            Vector2 neighbor1 = levelMap[level][index-1]->getPosition();
            Vector2 newPosition = {(neighbor1.x + 80), neighbor1.y};
            return newPosition;
        }

        else if (index ==0 ){
            Vector2 neighbor1 = levelMap[level][index+1]->getPosition();
            Vector2 newPosition = {(neighbor1.x - 80), neighbor1.y};
            return newPosition;
        }
    }
    return {0,0};
}

int Trie_Scene::calculateIndex(int level, const char word){
    int index =0;
    int parentLevel = level - 80;
    if (level == 180) {
        if(cur->children.empty()) return 0;
        else{
            index = std::distance(cur->children.begin(), cur->children.lower_bound(word));
        }
    }

    else {

        if (levelMap[parentLevel].empty()) return 0;
        for (TrieNodePrimary* parentNode : levelMap[parentLevel]) {
            if (parentNode != cur) {
                index += parentNode->children.size();
            } else {
                index += std::distance(cur->children.begin(), cur->children.lower_bound(word));
                break;
            }
        }
        //std::cout << " Runned " << index << "\n";
    }
    return index;
}

void Trie_Scene::updateHelper(){
    int lev=proot->getPosition().y +80;
    while (levelMap.find(lev) != levelMap.end() && !levelMap[lev].empty()){
        for (TrieNodePrimary* node : levelMap[lev]){
            node->onClick();
            if (node->isupdate && node->trueUpdate){
                if(!node->input.empty() && node->input[0]!=node->key && isValid(node,lev,node->input[0])){
                    for (TrieNodePrimary* parent : levelMap[lev - 80]) {
                        auto it = parent->children.find(node->key);
                        if (it != parent->children.end() && it->second == node) {
                            parent->children[node->input[0]] = node;
                            parent->children.erase(it);
                            break;
                        }
                    }
                    std::cout << "update success" << "\n";
                    node->key= node->input[0];

                }

                std::cout << "non update success" << "\n";
                node->isupdate=false;
                node->trueUpdate=false;
                node->input.clear();
                if(!node->isEndOfWord)node->SetNullHighLight();

            }
        }
        lev=lev+80;
    }
}

bool Trie_Scene::isValid(TrieNodePrimary* node, int level, const char c){
    int lev = level - 80;
    for (TrieNodePrimary* parent : levelMap[lev]){
        if(!parent->children.empty()){
            if (parent->children.find(node->key)!=parent->children.end() && parent->children[node->key]==node){
                if (parent->children.find(node->input[0])==parent->children.end()) {
                    return true;
                }
            }
        }
    }
    return false;

}

void Trie_Scene::UndoTrie(){
    if(!history.empty() && (ani_state==Undo|| ani_state==Backward)){
        std::pair<InputType, std::string> current;
        current = history.top();
        history.pop();
        future.push(current);
        std::cout<<"Undoing "<< current.first<<" "<< current.second<<"\n";
        if(current.first==InputType::Insert){
            buffer += "1 ";
            buffer += current.second + " ";
        }
        else if(current.first==InputType::Remove){
            buffer+= "0";
            buffer+=current.second+ " ";
        }
        pushed = true;
        if (ani_state==Undo) ani_state=Pause;
    }
}

void Trie_Scene::RedoTrie(){
    if(!future.empty() && (ani_state==Redo|| ani_state==Forward)){
        std::pair<InputType, std::string> current;
        current = future.top();
        future.pop();
        // history.push(current);
        // std::cout<<"Redoing "<< current.first<<" "<< current.second<<"\n";
        if(current.first==InputType::Insert){
            buffer += "0";
            buffer += current.second;
        }
        else if(current.first==InputType::Remove){
            buffer+= "1";
            buffer+=current.second;
        }
    }
}

void Trie_Scene::loadFromFile(){
        const char* filter[] = { "*.txt" };
        const char* filePath = tinyfd_openFileDialog(
            "Select a Trie command file",
            "",
            1,
            filter,
            "Text file (*.txt)",
            0
        );
    
        if (filePath) {
            std::ifstream fin(filePath);
            if (!fin.is_open()) {
                std::cerr << "Error: Cannot open file\n";
                return;
            }
    
            std::cout << "Loading commands from: " << filePath << "\n";
    
            int commandType;
            std::string word;
            while (fin >> commandType >> word) {
                std::cout << "Command: " << commandType << ", Word: " << word << "\n";
                switch (commandType) {
                    case 0:  // Insert
                        buffer+= "0 "  ;
                        buffer += word + " "; 

                    case 1:  // Remove
                        buffer+= "1 "  ;
                        buffer += word+" "; 
                    case 3:  // Search
                        buffer+= "3 "  ;
                        buffer += word + " "; 
                        break;
                    default:
                        std::cerr << "Unknown command type: " << commandType << "\n";
                        break;
                }
            }
    
            fin.close();
        }
    }
    

void Trie_Scene::clear(){
    while(!history.empty()){
        CheckBuffer();
        
            std::pair<InputType, std::string> current;
            current = history.top();
            history.pop();
            future.push(current);
            std::cout<<"Undoing "<< current.first<<" "<< current.second<<"\n";
            if(current.first==InputType::Insert){
                buffer += "1 ";
                buffer += current.second + " ";
            }
        pushed = true;
        if (ani_state==Undo) ani_state=Pause;
        
    }
}


void Heap_Scene::run(Scenes& mscene) 
{
    /* UI::wWidth = static_cast<float>(GetScreenWidth());
    UI::wHeight = static_cast<float>(GetScreenHeight());
    float deltatime = IsWindowFocused() ? GetFrameTime() : 0;
    ClearBackground(BLACK);
    DrawCommonUI();
    DrawText("Heap", 200, 200, 40, WHITE);
    CheckBuffer();
    if (IsKeyPressed(KEY_LEFT)) {
        mscene = Menu;
        return;
    }
    BeginMode2D(UI::camera);
    UI::mousePos = GetScreenToWorld2D(GetMousePosition(), UI::camera);
    Draw();
    EndMode2D();
    UI::mousePos = GetMousePosition();
    DrawButtons();
 */

    ClearBackground(THEME.BACKGROUND);
    maxHeap.draw();
    tittle.draw();
    maxHeap.handle();
    if (tittle.handle() == 1) {
        mscene = Menu;
        return;
    }
}

/* void Heap_Scene::Draw() {
    Max_Heap::drawHeap(Mheap.animation, Mheap.font);
} */



void NodeScene::updateStep(int index) {
    
    this->stepindex = index; 

    
}


void NodeScene::drawButtons() {
    this->createButton.draw(50);
    this->deleteButton.draw(50);
    this->pushButton.draw(50);
    this->searchButton.draw(50); 
    if(this->isGraph)
    {
        this->dijkstrabutton.draw(50); 
        this->addedgeButton.draw(50);
    }

    if(this->isCreateChosen) {
        this->randomButton.draw();
        this->loadFileButton.draw();
    }
    if(this->isDeleteChosen || this->isPushChosen||this->isSearchChosen|| (isGraph && (isdijkstraChosen||isaddedgeChosen))) {
        this->inputNumber.draw();
        this->inputNumber.update();
        this->playButton.draw();
    }
    if(this->isDeleteChosen)
    {
        this->clearButton.draw();
    }
 
}




std::string formatInput2(const std::string& type, const std::string& input) {
    std::stringstream ss(input);
    std::vector<std::string> words;
    std::string word, result;

    while (ss >> word) {
        words.push_back(type + " " + word);
    }
    for (const std::string& w : words) {
        result += w + " ";
    }

    return result;
}

std::string  formatInputAddEdge2(const std::string& type, const std::string& input) {
    std::stringstream ss(input);
    std::vector<std::string> words;
    std::string from, to, weight, result;

    while (ss >> from && ss>>to && ss>>weight) {
        words.push_back(type + " " + from+" "+to+" "+weight);
    }
    for (const std::string& w : words) {
        result += w + " ";
    }

    return result;
}

int Singly_Scene::handle() {
    this->type = (ani_state ==Pause) ?  0 : 1;  
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        if (this->createButton.getIsHovered()) {
            this->isCreateChosen = true;
            this->isDeleteChosen = false;
            this->isPushChosen = false;
            this->isSearchChosen = false; 
        }
        if (this->deleteButton.getIsHovered()) {
            this->isCreateChosen = false;
            //this->inputNumber.resetText();
            this->isDeleteChosen = true;
            this->isPushChosen = false;
            this->isSearchChosen = false; 

        }
        if (this->pushButton.getIsHovered()) {
            this->isCreateChosen = false;
            this->isDeleteChosen = false;
            //this->inputNumber.resetText();
            this->isPushChosen = true;
            this->isSearchChosen = false; 

        }
        if (this->searchButton.getIsHovered()) {
            this->isCreateChosen = false;
            this->isDeleteChosen = false;
            //this->inputNumber.resetText();
            this->isPushChosen = false;
            this->isSearchChosen = true; 
        }
    }

    if (this->playButton.handle()) {
        if (this->isPushChosen) {
            std::string input =  this->inputNumber.getText(); 
            this->inputNumber.resetText();
            if(input!="")
           {  
             buffer += formatInput2("0",' ' +input + ' '); 
            input =""; 
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            ani_state = Continue; 

            return 2;
        }
        if (this->isDeleteChosen) {
            
            std::string input =  this->inputNumber.getText(); 
            this->inputNumber.resetText();
            if(input!="")
           {  
             buffer += formatInput2("1",' ' +input + ' '); 
            input =""; 
            }
            ani_state = Continue; 
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            return 3;
        }
        if(this->isSearchChosen)
        {
            std::string input =  this->inputNumber.getText(); 
            this->inputNumber.resetText();
            if(input!="")
           {  
             buffer += formatInput2("3",' ' +input + ' '); 
            input =""; 
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            ani_state = Continue; 
            return 4; 
        }
    }


    if (this->randomButton.handle()) {
        ClearHistory();
        int n = std::rand() % 11 +1; 
        for(int i =0 ; i <n;i++)
        {
            Vector2 pos = {static_cast<float>(std::rand() % GetScreenWidth()), static_cast<float>(std::rand() % GetScreenHeight())};
            if (pos.x + 500 < GetScreenWidth()) pos.x += 500;
            if (pos.y + 200 < GetScreenHeight()) pos.y += 200;
            if (pos.x > GetScreenWidth() - 100) pos.x -= 100;
            if (pos.y > GetScreenHeight() - 100) pos.y -= 100;
            int value = std::rand() % 1000;
            addFunction(animation_queue,++cur_priority, std::bind(&Ani_InsertRandomList ::updateTarget, &insert_2, pos,value));       
        }
        addFunction(animation_queue,++cur_priority,std::bind(&Ani_Straighten::updateTarget, &st, Vector2{100,100}));
        return 1;
    }
    if (this->loadFileButton.handle()) {
        // createFromFile();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        return 5;
    }

    int flag = this->progressBar.handle();

    switch (flag)
    {
        case -2:
            if (maxsteps == 0) break;
            ani_state = FirstState; 
            stepindex = 0; 
            
            break;

        case -1:
            if (maxsteps == 0) return 0;
            ani_state = Backward;  
            stepindex -= 1; 
            break;

        case 1:
             if (maxsteps == 0) return 0;
             ani_state = Forward; 
             stepindex += 1; 
            break;

        case 2:
            if (maxsteps == 0) return 0;
            ani_state = FinalState; 
            stepindex = maxsteps; 
            this->type = 2;
            break;

        case 0:
            if (this->type == 2) {
                if (maxsteps == 0) return 0;
                this->ani_state = FirstState;
                stepindex = 0 ;   
                this->type = 0;
                break;
            }
            if (this->type == 1) {
                ani_state = Pause;  
                this->type = 0;
                break;
            }
            if (this->type == 0 && ani != None) {
                ani_state = Continue; 
                this->type = 1;
                break;
            }
            break;

        case 3:
           speed += 0.1f;

            break;
        case -3:
            speed -= 0.1f;
        default:
            break;
    }

    return 0;
}
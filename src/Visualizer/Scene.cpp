#include "Scene.h"
#include "UI.h"
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
void Singly_Scene::run(Scenes& mscene)
{
    float deltaTime = IsWindowFocused() ? GetFrameTime() : 0;
    ClearBackground(BLACK);
    DrawText("Singly Linked List", 200, 200, 40, WHITE);
    if (IsKeyPressed(KEY_LEFT)) {
        mscene = Menu;
        created = false;
        list.DeleteList();
        a = Ani_LinkedListTraversal();
        return; 
    }
    
    if (!created) {
        list.Insert(5);
        list.Insert(3);
        list.Insert(7);
        list.Insert(15);
        list.Insert(12);
        list.Insert(20);
        a = Ani_LinkedListTraversal(0.3, list.get_root(), Vector2({300, 300}), 20);
        created = true;
    }
    a.updateAnimations(deltaTime);
    a.Draw();
}
SceneManager::SceneManager()
{
    mscene = Welcome;
    scenes.push_back(new Welcome_Scene()); 
    scenes.push_back(new Menu_Scene()); 
    scenes.push_back(new Singly_Scene()); 
}
SceneManager::~SceneManager() {
    for (Scene* scene : scenes) {
        delete scene;  
    }
    scenes.clear();
}
NodeScene::NodeScene()
{
    DrawText("Node Scene", 300, 200, 30, WHITE);
}
Singly_Scene::Singly_Scene(): NodeScene(),a(0.3, nullptr, Vector2({300, 300}), 20), created(false)
{}
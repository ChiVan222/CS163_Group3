#include "InputField.h"
#include "UI.h"
void InputField::Activate()
{
  isActive = true; 
}
InputField::InputField(float width, float height, Vector2 position, InputType type): type(type)
{
   inputbox.x = position.x;
   inputbox.y = position.y; 
   inputbox.height = height;
   inputbox.width = width;  
   isActive = false;
   const char* title;
   last_deletedtime = 0 ; 
   wait_time = 0.1; 
   switch(type)
   { 
     
     case(InputType::Insert):
     {
       title=  "Insert" ;
     }break;
     case(InputType::Remove):
     {
        title = "Remove"; 
     }break;
     case(InputType::Update):
     {
        title = "Update" ;
     }break;
     case(InputType::Search):
     {
        title = "Search";
     }break;
     case(InputType::AddEdge):
     {
        title  = "AddEdge";
     }break; 
   }
   button = new Button("",Vector2({inputbox.x+inputbox.width, inputbox.y}),Vector2({100,inputbox.height}),title);
}
InputField::InputField(Rectangle rec)
{
    
    inputbox = rec; 
}
void InputField::Deactivate()
{
    isActive =false; 
}
void InputField::HandleInput(std::string& buffer,Vector2 mousePos)
{ 
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, inputbox)) {
            isActive = true;
    } else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            isActive = false;
    }
    
    if(isActive)
    {
        int key =GetCharPressed();
        while(key>0)
        {       
            if(key>=32 && key<= 125 && input.size()<max_input)
            {
                input +=  (char)key; 
            }
            key = GetCharPressed();
        }
        if(GetTime() - last_deletedtime >= wait_time)
        { 
            if(IsKeyDown(KEY_BACKSPACE)&& !input.empty())
            {
                input.pop_back(); 
                last_deletedtime  = GetTime(); 
            }
        }
        
       
    }
}
#include <sstream>
std::string formatInput(const std::string& type, const std::string& input) {
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
std::string  formatInputAddEdge(const std::string& type, const std::string& input) {
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
bool InputField::Send(std::string& buffer)
{
    
    if(IsKeyPressed(KEY_ENTER)||((button->IsHovered(UI::mousePos)&& IsMouseButtonPressed(MOUSE_BUTTON_LEFT))))
    {
        Singly_Scene::ClearHistory();
        if(input!="")
       {  
        if(type == AddEdge) buffer += formatInputAddEdge(std::to_string(static_cast<int>(type)),' ' +input +" ");
        else buffer += formatInput(std::to_string(static_cast<int>(type)),' ' +input + ' '+ prevInput + " "); 
        input =""; 
        return true; }
    }
    DrawText(("Buffer: " +buffer).c_str(), 0,0,20,WHITE);
    return false; 
}
void InputField::Draw(bool DrawButton)
{
    DrawRectangleRec(inputbox, isActive? LIGHTGRAY:GRAY); 
    DrawText(input.c_str(), inputbox.x + 10, inputbox.y + 15, 20, BLACK);
    if(DrawButton){ 
        button->Draw();
        button->DrawButtonText_center();
    }
}
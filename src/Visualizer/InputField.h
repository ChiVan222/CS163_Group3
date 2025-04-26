#include <string>
#include <raylib.h> 
#include "Button.h"
#include "Utility.h"
#pragma once
class InputField 
{ 
    
    private:
     static constexpr int max_input = 20; 
     std::string input; 
     std::string prevInput; 
     Rectangle inputbox; 
     InputType type; 
     bool isActive;
     float wait_time; 
     Button* button; 
     float last_deletedtime; 
    public :   
     bool Send(std::string & buffer); 
     void HandleInput(std::string& buffer,Vector2 mousePos); 
     void Activate(); 
     void Deactivate();
     void Draw(bool DrawButton); 
     InputField(Rectangle rec);
     InputField(float width, float height, Vector2 position, InputType type);
     Vector2 getPosition() {
        return {inputbox.x, inputbox.y}; 
     }
     void setPosition(Vector2 pos) {
        inputbox.x = pos.x;
        inputbox.y = pos.y;
     }
}; 
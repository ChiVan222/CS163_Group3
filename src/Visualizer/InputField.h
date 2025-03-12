#include <string>
#include <raylib.h> 
#pragma once
class InputField 
{ 
    private:
     static constexpr int max_input = 20; 
     std::string input; 
     Rectangle inputbox; 
     bool isActive;
    public :   
     void Send(std::string & buffer); 
     void HandleInput(std::string& buffer,Vector2 mousePos); 
     void Activate(); 
     void Deactivate();
     void Draw(); 
     InputField(Rectangle rec);
     InputField(float width, float height, Vector2 position);
}; 
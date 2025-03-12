#include "InputField.h"
void InputField::Activate()
{
  isActive = true; 
}
InputField::InputField(float width, float height, Vector2 position)
{
   inputbox.x = position.x;
   inputbox.y = position.y; 
   inputbox.height = height;
   inputbox.width = width;  
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
            if(key>=32 && key<= 125)
            {
                input +=  (char)key; 
            }
            key = GetCharPressed();
        }
        if(IsKeyPressed(KEY_BACK)&& !input.empty())
        {
            input.pop_back(); 
        }
        if(IsKeyPressed(KEY_ENTER))
        {
            Send(buffer); 
        }
    }
}
void InputField::Send(std::string& buffer)
{
  buffer +=  input; 
  input =""; 
}
void InputField::Draw()
{
    DrawRectangleRec(inputbox, isActive? LIGHTGRAY:GRAY); 
    DrawText(input.c_str(), inputbox.x + 10, inputbox.y + 15, 20, BLACK);
}
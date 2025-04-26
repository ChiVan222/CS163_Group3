#include "TrieNode.h"
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include "Scene.h"
#include "UI.h"

TrieNodePrimary::TrieNodePrimary(Vector2 pos, float radius, char key)
    : PolyNode(pos, radius), key(key), isEndOfWord(false), isupdate(false) {
        children.clear();
        lastDeletedTime = 0.0f;
        input.clear();
        trueUpdate=false;
        deleting = false;
    }


// bool TrieNodePrimary::Draw() {
//     DrawNode();
//     int textSize = radius;
//     char text[2] = {input[0], '\0'};
//     int textWidth = MeasureText(text, textSize);
//     int textHeight = textSize; 
//     int textX = position.x - textWidth / 2;
//     int textY = position.y - textHeight / 2;
//     DrawText(text, textX, textY, radius, WHITE);

//     return true;
// }
bool TrieNodePrimary::Draw() {
    DrawNode(); // Vẽ node

    int textSize = radius;
    char text[2] = {key, '\0'};
    const char* displayChar;

    static char tempChar[2] = {'_', '\0'}; // placeholder khi input rỗng

    if (isupdate) {
        if (!input.empty()) {
            displayChar = input.c_str();
        } 
        else {
            displayChar = tempChar;  
        }
    } 
    else {
        displayChar = text;
    }

    int textWidth = MeasureText(displayChar, textSize);
    int textHeight = textSize;
    int textX = position.x - textWidth / 2;
    int textY = position.y - textHeight / 2;

    DrawText(displayChar, textX, textY, textSize, WHITE);
    return true;
}


void TrieNodePrimary::SetEndOfWord(bool isEnd) {
    isEndOfWord = isEnd;
}

TrieNodePrimary::~TrieNodePrimary() {
    clear();  
}


void TrieNodePrimary::clear(TrieNodePrimary* node) {
    if (!node) {
        return;
    }
    for (auto& pair : node->children) {
        clear(pair.second);
    }
    node->children.clear();
    if (node!= Trie_Scene::proot) delete node;
}


void TrieNodePrimary::clear() {
    clear(Trie_Scene::proot);
}
//


//
void TrieNodePrimary::Traverse(TrieNodePrimary* node) {
    if (!node) return; 
    node->Draw();  
    for (auto& child : node->children) {
        TrieNodePrimary* childNode = child.second;
        Traverse(childNode);
    }
}

void TrieNodePrimary::onClick() {
    if (Trie_Scene::ani == None) {
        Vector2 mousePos = UI::mousePos;
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointCircle(mousePos, position, 30)) {
                isupdate = true;
                SetPrimaryHighLight();
                std::cout << "true update" << "\n";
            } 
            else {
                input.clear();
                if (!isEndOfWord)SetNullHighLight();
                isupdate = false;
            }
        }

        if (isupdate) {
            int val = GetCharPressed();
            while (val > 0) {
                if (val >= 32 && val <= 125 && input.size() < 1) {
                    input += (char)val;
                }
                val = GetCharPressed();
                std::cout << "get char" << "\n";
            } 

            if (GetTime() - lastDeletedTime >= waitTime) {
                if (IsKeyDown(KEY_BACKSPACE) && !input.empty()) {
                    input.pop_back();
                    lastDeletedTime = GetTime();
                }
            }

            if (IsKeyDown(KEY_ENTER) && input.size() == 1) {
                trueUpdate=true;
                return;
            }
        }
    }

}

bool TrieNodePrimary::canDelete(TrieNodePrimary* node) {
    for (auto& [ch, child] : node->children) {
        if (!child->deleting) return false;
    }
    return true;
}


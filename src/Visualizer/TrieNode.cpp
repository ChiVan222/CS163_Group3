#include "TrieNode.h"
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include "Scene.h"

TrieNodePrimary::TrieNodePrimary(Vector2 pos, float radius, char key)
    : PolyNode(pos, radius), key(key), isEndOfWord(false), isDeleted(false) {
        children.clear();
    }


bool TrieNodePrimary::Draw() {
    Color default_color ={74, 144, 226, 225};
    Color last = {0, 173, 181, 255};

    Color primary_color = RED;
    Color secondary_color = ORANGE;
    float outline_thickness = 5.0f; 

    if (highlight == Primary) {
        DrawCircle(position.x, position.y, radius + outline_thickness, primary_color);
    } else if (highlight == Secondary) {
        DrawCircleLines(position.x, position.y, radius + outline_thickness, secondary_color);
    }

    Color node_color = isEndOfWord ? last : default_color; 
    DrawCircle(position.x, position.y, radius, node_color);
    DrawCircleLines(position.x, position.y, radius, WHITE);

    int textSize = radius;
    char text[2] = {key, '\0'};
    int textWidth = MeasureText(text, textSize);
    int textHeight = textSize; 
    int textX = position.x - textWidth / 2;
    int textY = position.y - textHeight / 2;
    DrawText(text, textX, textY, radius, WHITE);

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
#pragma once
#include <map>
#include <string>
#include "PolyNode.h"


class TrieNodePrimary : public PolyNode {
public:
    char key;
    std::string input;
    bool isEndOfWord;
    bool isupdate;
    float lastDeletedTime ;
    const float waitTime =0.1f;
    bool trueUpdate;
    bool deleting;
    std::map<char, TrieNodePrimary*> children;
    
    ~TrieNodePrimary();
    void clear() ;
    void clear(TrieNodePrimary* node);
    void Traverse(TrieNodePrimary* node);
    TrieNodePrimary(Vector2 pos, float radius, char value);
    bool Draw() override;
    void SetEndOfWord(bool isEnd);
    void onClick();
    bool canDelete(TrieNodePrimary* node);
};


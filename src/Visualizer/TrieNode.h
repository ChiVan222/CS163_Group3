#pragma once
#include <map>
#include <string>
#include "PolyNode.h"


class TrieNodePrimary : public PolyNode {
public:
    char key;
    bool isEndOfWord;
    bool isDeleted;
    std::map<char, TrieNodePrimary*> children;
    
    ~TrieNodePrimary();
    void clear() ;
    void clear(TrieNodePrimary* node);
    void Traverse(TrieNodePrimary* node);
    TrieNodePrimary(Vector2 pos, float radius, char value);
    bool Draw() override;
    void SetEndOfWord(bool isEnd);
};


#pragma once
#include <iostream>
#include <map>
using namespace std;

class Trie {
private:
    struct TrieNode {
        map<char, TrieNode*> children;
        bool EndofWord;
        TrieNode() : EndofWord(false) {}
    };

    TrieNode* proot;

    void clear(TrieNode* node);  
    bool removeWord(TrieNode* node, const string& word, int depth);

public:
    Trie();
    ~Trie();
    
    void insert(const string& word);
    bool search(const string& word);
    bool removeWord(const string& word);
    void clear(); 
};

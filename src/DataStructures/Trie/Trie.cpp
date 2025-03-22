#include "Trie.h"


Trie::Trie() {
    proot = new TrieNode();
}


Trie::~Trie() {
    clear();  
}


void Trie::clear(TrieNode* node) {
    if (!node) 
        return;
    
    for (auto& pair : node->children) {
        clear(pair.second);
    }
    node->children.clear();
    delete node;
}


void Trie::clear() {
    clear(proot);
    delete proot;
}


void Trie::insert(const string& word) {
    TrieNode* temp = proot;

    for (char ch : word) {
        if (temp->children.find(ch) == temp->children.end()) {
            temp->children[ch] = new TrieNode();
        }
        temp = temp->children[ch];
    }

    temp->EndofWord = true;
}

bool Trie::search(const string& word) {
    TrieNode* temp = proot;

    for (char ch : word) {
        if (temp->children.find(ch) == temp->children.end()) {
            return false;
        }
        temp = temp->children[ch];
    }

    return temp->EndofWord;
}


bool Trie::removeWord(TrieNode* node, const string& word, int depth) {
    if (!node) return false;

    if (depth == word.size()) {
        if (!node->EndofWord) return false;  
        node->EndofWord = false;  

        return node->children.empty();  
    }

    char ch = word[depth];
    if (removeWord(node->children[ch], word, depth + 1)) {
        delete node->children[ch];
        node->children.erase(ch);
        return !node->EndofWord && node->children.empty();
    }
    return false;
}


bool Trie::removeWord(const string& word) {
    return removeWord(proot, word, 0);
}

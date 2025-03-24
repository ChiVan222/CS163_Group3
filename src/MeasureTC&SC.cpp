#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cstring>
#include <chrono>
#include <windows.h>
#include <psapi.h>

using namespace std;
using namespace chrono;

#define ALPHABET_SIZE 26
#define NUM_WORDS 10000  // Num of words
#define WORD_LENGTH 10     // Word length

// Trie with map
struct TrieNodeMap {
    unordered_map<char, TrieNodeMap*> children;
    bool isEnd;
    TrieNodeMap() { isEnd = false; }
};

class TrieMap {
public:
    TrieNodeMap* root;
    TrieMap() { root = new TrieNodeMap(); }

    void insert(const string& word) {
        TrieNodeMap* node = root;
        for (char c : word) {
            if (node->children.find(c) == node->children.end())
                node->children[c] = new TrieNodeMap();
            node = node->children[c];
        }
        node->isEnd = true;
    }

    bool search(const string& word) {
        TrieNodeMap* node = root;
        for (char c : word) {
            if (node->children.find(c) == node->children.end())
                return false;
            node = node->children[c];
        }
        return node->isEnd;
    }

    bool remove(const string& word) {
        return removeHelper(root, word, 0);
    }

    ~TrieMap() { deleteTrie(root); }

private:
    bool removeHelper(TrieNodeMap* node, const string& word, int depth) {
        if (!node) return false;
        if (depth == word.size()) {
            if (!node->isEnd) return false;
            node->isEnd = false;
            return node->children.empty();
        }
        char c = word[depth];
        if (node->children.find(c) == node->children.end()) return false;
        if (removeHelper(node->children[c], word, depth + 1)) {
            delete node->children[c];
            node->children.erase(c);
            return !node->isEnd && node->children.empty();
        }
        return false;
    }

    void deleteTrie(TrieNodeMap* node) {
        if (!node) return;
        for (auto& pair : node->children)
            deleteTrie(pair.second);
        delete node;
    }
};

// Trie with array
struct TrieNodeArray {
    TrieNodeArray* children[ALPHABET_SIZE];
    bool isEnd;
    TrieNodeArray() {
        memset(children, 0, sizeof(children));
        isEnd = false;
    }
};

class TrieArray {
public:
    TrieNodeArray* root;
    TrieArray() { root = new TrieNodeArray(); }

    void insert(const string& word) {
        TrieNodeArray* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx])
                node->children[idx] = new TrieNodeArray();
            node = node->children[idx];
        }
        node->isEnd = true;
    }

    bool search(const string& word) {
        TrieNodeArray* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx])
                return false;
            node = node->children[idx];
        }
        return node->isEnd;
    }

    bool remove(const string& word) {
        return removeHelper(root, word, 0);
    }

    ~TrieArray() { deleteTrie(root); }

private:
    bool removeHelper(TrieNodeArray* node, const string& word, int depth) {
        if (!node) return false;
        if (depth == word.size()) {
            if (!node->isEnd) return false;
            node->isEnd = false;
            return all_of(begin(node->children), end(node->children), [](TrieNodeArray* child) { return child == nullptr; });
        }
        int idx = word[depth] - 'a';
        if (!node->children[idx]) return false;
        if (removeHelper(node->children[idx], word, depth + 1)) {
            delete node->children[idx];
            node->children[idx] = nullptr;
            return !node->isEnd && all_of(begin(node->children), end(node->children), [](TrieNodeArray* child) { return child == nullptr; });
        }
        return false;
    }

    void deleteTrie(TrieNodeArray* node) {
        if (!node) return;
        for (int i = 0; i < ALPHABET_SIZE; i++)
            if (node->children[i]) deleteTrie(node->children[i]);
        delete node;
    }
};

// Array & Hashmap
vector<string> wordList;
unordered_set<string> wordSet;

void insertArray(const string& word) { wordList.push_back(word); }
bool searchArray(const string& word) { return find(wordList.begin(), wordList.end(), word) != wordList.end(); }
void removeArray(const string& word) { wordList.erase(remove(wordList.begin(), wordList.end(), word), wordList.end()); }

void insertHash(const string& word) { wordSet.insert(word); }
bool searchHash(const string& word) { return wordSet.find(word) != wordSet.end(); }
void removeHash(const string& word) { wordSet.erase(word); }

// Generate Random Words
string generateRandomWord(int length) {
    string word;
    for (int i = 0; i < length; i++) {
        word += 'a' + rand() % 26;
    }
    return word;
}

// Measure time
template <typename Func>
double measureTime(Func function) {
    auto start = high_resolution_clock::now();
    function();
    auto end = high_resolution_clock::now();
    return duration<double, milli>(end - start).count();
}


// Measure memory
double getMemoryUsage() {
    PROCESS_MEMORY_COUNTERS memInfo;
    GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo));
    return static_cast<double>(memInfo.WorkingSetSize);
}

int main() {
    srand(time(0));  
    vector<string> words;
    for (int i = 0; i < NUM_WORDS; i++) {
        words.push_back(generateRandomWord(WORD_LENGTH));
    }

    TrieMap trieMap;
    TrieArray trieArray;

    // Insert
    cout << "===> INSERT TIME (ms) <===" << endl;
    cout << "Trie (unordered_map): " << measureTime([&]() { for (const string& word : words) trieMap.insert(word); }) << " ms" << endl;
    cout << "Trie (array): " << measureTime([&]() { for (const string& word : words) trieArray.insert(word); }) << " ms" << endl;
    cout << "Array (vector<string>): " << measureTime([&]() { for (const string& word : words) insertArray(word); }) << " ms" << endl;
    cout << "Hashmap (unordered_set): " << measureTime([&]() { for (const string& word : words) insertHash(word); }) << " ms" << endl;

    // Search
    cout << "\n===> SEARCH TIME (ms) <===" << endl;
    cout << "Trie (unordered_map): " << measureTime([&]() { for (const string& word : words) trieMap.search(word); }) << " ms" << endl;
    cout << "Trie (array): " << measureTime([&]() { for (const string& word : words) trieArray.search(word); }) << " ms" << endl;
    cout << "Array (vector<string>): " << measureTime([&]() { for (const string& word : words) searchArray(word); }) << " ms" << endl;
    cout << "Hashmap (unordered_set): " << measureTime([&]() { for (const string& word : words) searchHash(word); }) << " ms" << endl;

    // Remove
    cout << "\n===> REMOVE TIME (ms) <===" << endl;
    cout << "Trie (unordered_map): " << measureTime([&]() { for (const string& word : words) trieMap.remove(word); }) << " ms" << endl;
    cout << "Trie (array): " << measureTime([&]() { for (const string& word : words) trieArray.remove(word); }) << " ms" << endl;
    cout << "Array (vector<string>): " << measureTime([&]() { for (const string& word : words) removeArray(word); }) << " ms" << endl;
    cout << "Hashmap (unordered_set): " << measureTime([&]() { for (const string& word : words) removeHash(word); }) << " ms" << endl;

    double beforeMem, afterMem;
    
    cout << "\n===> INSERT MEMORY (KB) <===" << endl;
    beforeMem = getMemoryUsage();
    for (const string& word : words) trieMap.insert(word);
    afterMem = getMemoryUsage();
    cout << "Trie (unordered_map) Memory Usage: " << (afterMem - beforeMem) / 1024.0 << " KB" << endl;

    beforeMem = getMemoryUsage();
    for (const string& word : words) trieArray.insert(word);
    afterMem = getMemoryUsage();
    cout << "Trie (array) Memory Usage: " << (afterMem - beforeMem) / 1024.0 << " KB" << endl;

    beforeMem = getMemoryUsage();
    for (const string& word : words) insertArray(word);
    afterMem = getMemoryUsage();
    cout << "Array (vector<string>) Memory Usage: " << (afterMem - beforeMem) / 1024.0 << " KB" << endl;

    beforeMem = getMemoryUsage();
    for (const string& word : words) insertHash(word);
    afterMem = getMemoryUsage();
    cout << "Hashmap (unordered_set) Memory Usage: " << (afterMem - beforeMem) / 1024.0 << " KB" << endl;

    cout << "\n===> SEARCH MEMORY (KB) <===" << endl;
    beforeMem = getMemoryUsage();
    for (const string& word : words) trieMap.search(word);
    afterMem = getMemoryUsage();
    cout << "Trie (unordered_map) Search Memory Usage: " << (afterMem - beforeMem) / 1024.0 << " KB" << endl;

    beforeMem = getMemoryUsage();
    for (const string& word : words) trieArray.search(word);
    afterMem = getMemoryUsage();
    cout << "Trie (array) Search Memory Usage: " << (afterMem - beforeMem) / 1024.0 << " KB" << endl;

    beforeMem = getMemoryUsage();
    for (const string& word : words) searchArray(word);
    afterMem = getMemoryUsage();
    cout << "Array (vector<string>) Search Memory Usage: " << (afterMem - beforeMem) / 1024.0 << " KB" << endl;

    beforeMem = getMemoryUsage();
    for (const string& word : words) searchHash(word);
    afterMem = getMemoryUsage();
    cout << "Hashmap (unordered_set) Search Memory Usage: " << (afterMem - beforeMem) / 1024.0 << " KB" << endl;

    cout << "\n===> REMOVE MEMORY (KB) <===" << endl;
    beforeMem = getMemoryUsage();
    for (const string& word : words) trieMap.remove(word);
    afterMem = getMemoryUsage();
    cout << "Trie (unordered_map) Remove Memory Usage: " << (afterMem - beforeMem) / 1024.0 << " KB" << endl;

    beforeMem = getMemoryUsage();
    for (const string& word : words) trieArray.remove(word);
    afterMem = getMemoryUsage();
    cout << "Trie (array) Remove Memory Usage: " << (afterMem - beforeMem) / 1024.0 << " KB" << endl;

    beforeMem = getMemoryUsage();
    for (const string& word : words) removeArray(word);
    afterMem = getMemoryUsage();
    cout << "Array (vector<string>) Remove Memory Usage: " << (afterMem - beforeMem) / 1024.0 << " KB" << endl;

    beforeMem = getMemoryUsage();
    for (const string& word : words) removeHash(word);
    afterMem = getMemoryUsage();
    cout << "Hashmap (unordered_set) Remove Memory Usage: " << (afterMem - beforeMem) / 1024.0 << " KB" << endl;
}

/* Output:
===> INSERT TIME (ms) <===
Trie (unordered_map): 228.23 ms
Trie (array): 68.7712 ms
Array (vector<string>): 2.8545 ms
Hashmap (unordered_set): 17.2963 ms

===> SEARCH TIME (ms) <===
Trie (unordered_map): 115.774 ms
Trie (array): 61.9503 ms
Array (vector<string>): 27185.5 ms
Hashmap (unordered_set): 12.0553 ms

===> REMOVE TIME (ms) <===
Trie (unordered_map): 177.638 ms
Trie (array): 121.777 ms
Array (vector<string>): 50017.1 ms
Hashmap (unordered_set): 15.7776 ms

===> INSERT MEMORY (KB) <===
Trie (unordered_map) Memory Usage: 15852 KB
Trie (array) Memory Usage: 17224 KB
Array (vector<string>) Memory Usage: 852 KB
Hashmap (unordered_set) Memory Usage: 364 KB

===> SEARCH MEMORY (KB) <===
Trie (unordered_map) Search Memory Usage: 0 KB
Trie (array) Search Memory Usage: 0 KB
Array (vector<string>) Search Memory Usage: 0 KB
Hashmap (unordered_set) Search Memory Usage: 0 KB

===> REMOVE MEMORY (KB) <===
Trie (unordered_map) Remove Memory Usage: -15872 KB
Trie (array) Remove Memory Usage: -17476 KB
Array (vector<string>) Remove Memory Usage: 0 KB
Hashmap (unordered_set) Remove Memory Usage: -588 KB
*/
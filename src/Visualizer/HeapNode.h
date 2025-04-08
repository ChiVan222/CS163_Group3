#pragma once
#include "PolyNode.h"
#include <vector>
using namespace std;

class HeapNode : public PolyNode {
private:
    struct Node {
        int value;
        Node* parent;
        Node* left;
        Node* right;
        Node(int val = 0, Node* p = nullptr, Node* l = nullptr, Node* r = nullptr)
            : value(val), parent(p), left(l), right(r) {}
    };

    Node* root;
    int heapSize;

    void heapifyUp(Node* node);
    void heapifyDown(Node* node);
    Node* getLastNode();
    void deleteNode(Node* node);
    void drawNode(Node* node, Vector2 parentPos, float angle, float distance) const;

public:
    HeapNode(Vector2 pos, float radius);
    ~HeapNode();

    void insert(int value);
    int extractMin();
    int getMin() const;
    bool Draw() override;
    bool isEmpty() const;
    int size() const;
};
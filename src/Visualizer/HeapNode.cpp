#include "HeapNode.h"
#include <stdexcept>
#include <raylib.h>
#include <cmath>
#include <string>
HeapNode::HeapNode(Vector2 pos, float radius) : PolyNode(pos, radius) {
    root = nullptr;
    heapSize = 0;
}

HeapNode::~HeapNode() {
    deleteNode(root);
}

void HeapNode::deleteNode(Node* node) {
    if (!node) return;
    deleteNode(node->left);
    deleteNode(node->right);
    delete node;
}

void HeapNode::heapifyUp(Node* node) {
    while (node->parent && node->value < node->parent->value) {
        swap(node->value, node->parent->value);
        node = node->parent;
    }
}

void HeapNode::heapifyDown(Node* node) {
    while (node->left) {
        Node* smallest = node;
        if (node->left && node->left->value < smallest->value) {
            smallest = node->left;
        }
        if (node->right && node->right->value < smallest->value) {
            smallest = node->right;
        }
        if (smallest == node) break;
        swap(node->value, smallest->value);
        node = smallest;
    }
}

HeapNode::Node* HeapNode::getLastNode() {
    if (!root) return nullptr;
    vector<Node*> level;
    level.push_back(root);
    while (!level.empty()) {
        vector<Node*> nextLevel;
        for (Node* node : level) {
            if (!node->left && !node->right && heapSize % 2 == 0) return node;
            if (node->left) nextLevel.push_back(node->left);
            if (node->right) nextLevel.push_back(node->right);
        }
        if (nextLevel.size() <= 1) return nextLevel.empty() ? level.back() : nextLevel.back();
        level = nextLevel;
    }
    return nullptr;
}

void HeapNode::insert(int value) {
    Node* newNode = new Node(value);
    heapSize++;
    if (!root) {
        root = newNode;
        position = {position.x, position.y}; // Vị trí gốc
        return;
    }

    vector<Node*> level;
    level.push_back(root);
    while (!level.empty()) {
        vector<Node*> nextLevel;
        for (Node* node : level) {
            if (!node->left) {
                node->left = newNode;
                newNode->parent = node;
                heapifyUp(newNode);
                return;
            }
            if (!node->right) {
                node->right = newNode;
                newNode->parent = node;
                heapifyUp(newNode);
                return;
            }
            nextLevel.push_back(node->left);
            nextLevel.push_back(node->right);
        }
        level = nextLevel;
    }
}

int HeapNode::extractMin() {
    if (!root) throw runtime_error("Heap is empty");

    int minValue = root->value;
    Node* last = getLastNode();
    if (heapSize == 1) {
        delete root;
        root = nullptr;
        heapSize--;
        return minValue;
    }

    root->value = last->value;
    if (last->parent->left == last) {
        last->parent->left = nullptr;
    } else {
        last->parent->right = nullptr;
    }
    delete last;
    heapSize--;
    heapifyDown(root);

    return minValue;
}

int HeapNode::getMin() const {
    if (!root) throw runtime_error("Heap is empty");
    return root->value;
}

bool HeapNode::isEmpty() const {
    return heapSize == 0;
}

int HeapNode::size() const {
    return heapSize;
}

void HeapNode::drawNode(Node* node, Vector2 parentPos, float angle, float distance) const {
    if (!node) return;

    Vector2 nodePos = {
        parentPos.x + distance * cos(angle),
        parentPos.y + distance * sin(angle)
    };

    Color nodeColor = (highlight == Primary) ? RED : ((highlight == Secondary) ? ORANGE : WHITE);
    DrawCircleV(nodePos, radius, nodeColor);
    DrawCircleLines(nodePos.x, nodePos.y, radius, BLACK);

    string text = to_string(node->value);
    int textSize = radius;
    int textWidth = MeasureText(text.c_str(), textSize);
    int textX = nodePos.x - textWidth / 2;
    int textY = nodePos.y - textSize / 2;
    DrawText(text.c_str(), textX, textY, textSize, BLACK);

    if (node != root) {
        DrawLineV(parentPos, nodePos, WHITE);
    }

    drawNode(node->left, nodePos, angle - PI / 4, distance * 0.7f);
    drawNode(node->right, nodePos, angle + PI / 4, distance * 0.7f);
}

bool HeapNode::Draw() {
    if (!root) return false;
    drawNode(root, position, 0, 100.0f);
    return true;
}
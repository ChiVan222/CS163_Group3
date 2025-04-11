#pragma once
#include <vector>
using namespace std;

class Heap {
private:
    struct Node {
        int value;
        Node(int val = 0) : value(val) {}
    };

    vector<Node> heap;

    int parent(int index) const { return (index - 1) / 2; }
    int leftChild(int index) const { return 2 * index + 1; }
    int rightChild(int index) const { return 2 * index + 2; }
    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    Heap();
    Heap(const vector<int>& arr);

    void insert(int value);
    int extractMin();
    int getMin() const;
    bool isEmpty() const;
    int size() const;
};
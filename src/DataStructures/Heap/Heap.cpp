#include "heap.h"
#include <stdexcept>

Heap::Heap() {
    heap.clear();
}

Heap::Heap(const vector<int>& arr) {
    heap.resize(arr.size());
    for (int i = 0; i < arr.size(); ++i) {
        heap[i] = Node(arr[i]);
    }
    for (int i = heap.size() / 2 - 1; i >= 0; --i) {
        heapifyDown(i);
    }
}

void Heap::heapifyUp(int index) {
    while (index > 0 && heap[parent(index)].value > heap[index].value) {
        swap(heap[parent(index)], heap[index]);
        index = parent(index);
    }
}

void Heap::heapifyDown(int index) {
    int minIndex = index;
    int left = leftChild(index);
    int right = rightChild(index);

    if (left < heap.size() && heap[left].value < heap[minIndex].value) {
        minIndex = left;
    }
    if (right < heap.size() && heap[right].value < heap[minIndex].value) {
        minIndex = right;
    }

    if (minIndex != index) {
        swap(heap[index], heap[minIndex]);
        heapifyDown(minIndex);
    }
}

void Heap::insert(int value) {
    heap.push_back(Node(value));
    heapifyUp(heap.size() - 1);
}

int Heap::extractMin() {
    if (heap.empty()) {
        throw runtime_error("Heap is empty");
    }

    int minValue = heap[0].value;
    heap[0] = heap.back();
    heap.pop_back();

    if (!heap.empty()) {
        heapifyDown(0);
    }

    return minValue;
}

int Heap::getMin() const {
    if (heap.empty()) {
        throw runtime_error("Heap is empty");
    }
    return heap[0].value;
}

bool Heap::isEmpty() const {
    return heap.empty();
}

int Heap::size() const {
    return heap.size();
}
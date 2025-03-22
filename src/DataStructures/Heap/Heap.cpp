#include "Heap.h"

Heap::Heap() {}

void Heap::heapifyDown(int index) {
    int size = (int)data.size();
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && data[left] > data[largest]) {
        largest = left;
    }
    if (right < size && data[right] > data[largest]) {
        largest = right;
    }
    if (largest != index) {
        std::swap(data[index], data[largest]);
        heapifyDown(largest);
    }
}

int Heap::createFromFile(const char* filename) {
    std::ifstream infile(filename);
    if (!infile) {
        std::cerr << "File could not be opened!" << std::endl;
        return 0;
    }
    data.clear();
    int number;
    while (infile >> number) {
        data.push_back(number);
    }
    infile.close();

    int size = (int)data.size();
    for (int i = size / 2 - 1; i >= 0; --i) {
        heapifyDown(i);
    }
    return 1;
}

void Heap::createWithRandomizedData(int n, int range) {
    srand((int)time(0));
    data.clear();
    for (int i = 0; i < n; i++) {
        data.push_back(rand() % range);
    }
    for (int i = (int)data.size() / 2 - 1; i >= 0; --i) {
        heapifyDown(i);
    }
}

void Heap::push(int value) {
    data.push_back(value);
    int index = (int)data.size() - 1;
    while (index > 0 && data[index] > data[(index - 1) / 2]) {
        std::swap(data[index], data[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

int Heap::deleteMax() {
    if (data.empty()) {
        return -1;
    }
    int maxValue = data[0];
    data[0] = data.back();
    data.pop_back();

    if (!data.empty()) {
        heapifyDown(0);
    }
    return maxValue;
}

int Heap::top() {
    if (data.empty()) {
        return -1;
    }
    return data[0];
}

int Heap::size() {
    return (int)data.size();
}
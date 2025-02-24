#ifndef Heap_hpp
#define Heap_hpp

#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>

class Heap {
private:
    std::vector<int> data;
    void heapifyDown(int index);

public:
    Heap();
    int createFromFile(const char* filename);
    void createWithRandomizedData(int n, int range);
    void push(int value);
    int deleteMax();
    int top();
    int size();
};

#endif 
#pragma once

#include "../DataStructures/Heap/Heap.h"
#include "CommonUI.h"
#include "Utility.h"
#include "iostream"
#include <thread>
#include <chrono>

class MaxHeapVisualize {
    private:
        MaxHeap heap;
        int type = 0;
        ProgressBar progressBar;
        int stepIndex;
        int frame;
        int numFrameOfAnimation;
        
        ButtonNew  createButton;
        bool isCreateChosen;
        ButtonNew randomButton;
        ButtonNew loadFileButton;
        
        
        ButtonNew pushButton;
        bool isPushChosen;
        ButtonNew deleteButton;
        bool isDeleteChosen;
        InputStr inputNumber;
        ButtonNew playButton;
        
        ButtonNew topButton;
        ButtonNew sizeButton;
        
        public:
        
        Font font;
        Max_Heap::Step animation;
        MaxHeapVisualize(Font font);
        MaxHeapVisualize() : MaxHeapVisualize(FONT) {} ;
        Max_Heap::Step getAinimation() { return this->animation;}
        void updateStep(int index);
        int updateAnimation();
        void updateStep();
        void createWithRandomizedData(int n, int range);
        void createFromFile();
        void push();
        void deleteNode();
        void getTop();
        void getSize();
        
        void drawButtons();
        int handle();
        void draw();
        int buttonHandle();
};
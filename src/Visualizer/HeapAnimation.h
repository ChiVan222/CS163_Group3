#ifndef HeapAnimation_h
#define HeapAnimation_h
#include "General.h"
#include "CommonUI.h"
#include "../DataStructures/Heap/Heap.h"
class MaxHeapVisualize {
    private:
        MaxHeap heap;
        Max_Heap::Step animation;
        int type = 0;
        ProgressBar progressBar;
        int stepIndex;
        int frame;
        int numFrameOfAnimation;
        
        Button  createButton;
        bool isCreateChosen;
        Button randomButton;
        Button loadFileButton;
        
        
        Button pushButton;
        bool isPushChosen;
        Button deleteButton;
        bool isDeleteChosen;
        InputStr inputNumber;
        Button playButton;
        
        Button topButton;
        Button sizeButton;
        
        Font font;
    public:
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
#endif /* MaxHeap_hpp */

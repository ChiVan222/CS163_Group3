#pragma once
enum Scenes{  
    Welcome = 0, Menu, Singly,Graph,Trie,Setting,Heap
} ;
enum InputType 
{
     Insert = 0 , Remove, Update, Search, AddEdge, Randomize, DijkstraRun
};
enum animation 
{ 
    None, Searching, Inserting, Updating, Removing, EdgeDrawing, Inserting_2, Straightening, DijkstraRunning
};
enum animation_state{ 
    Backward = -1, Pause, Forward, Continue, FirstState, FinalState
};   

enum display{
    myfont =0, theme
};
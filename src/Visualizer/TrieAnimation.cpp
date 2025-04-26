#include "TrieAnimation.h"
#include "Scene.h"
#include <iostream>
//Trie Insert
Ani_TrieInsert::Ani_TrieInsert() : Animations(0), node_insert(nullptr), inserted(false), radius(20) {
    isDone = true;
 }

 Ani_TrieInsert::Ani_TrieInsert(float duration) : Animations(duration), node_insert(nullptr), inserted(false), radius(20) {}


void Ani_TrieInsert::updateTarget(Vector2 targetPos, float radius, TrieNodePrimary* node) {
    this->targetPos = targetPos;
    this->radius = radius;
    this->node_insert = node;
    startPos = Vector2({100, 100});  
    play(); 
 }

 // Khởi động animation
 void Ani_TrieInsert::play() {
     elapsed_time = 0;
     isDone = false;
     inserted = false;
 }

 // Cập nhật vị trí node mỗi frame
 void Ani_TrieInsert::updateAnimations(float deltaTime) {
     if (isDone || !node_insert|| Trie_Scene::state==Pause) return;

     elapsed_time += deltaTime;
     float t = elapsed_time / duration;
    if (t > 1.0f || Trie_Scene::ani_state==Forward 
        || Trie_Scene::ani_state==Backward) t = 1.0f;
     Vector2 newPos = Vector2({
         startPos.x + t * (targetPos.x - startPos.x),
         startPos.y + t * (targetPos.y - startPos.y)
     });

     node_insert->SetPosition(newPos);
     if (t >=1.0f) {
         isDone = true;
         inserted = true;
         Trie_Scene::ani = Updating;
     }
 }

 bool Ani_TrieInsert::isInserted() const {
     return inserted;
 }
 void Ani_TrieInsert::setDuration(float nduration){
     duration = nduration;
 }

 TrieNodePrimary* Ani_TrieInsert::getNode() const {
     return node_insert;
 }
// Trie Delete

Ani_TrieDelete::Ani_TrieDelete() : Animations(0) {
    isDone = true;
 }


void Ani_TrieDelete::play(){
    std::cout << "Update play"<< "\n";
    elapsed_time = 0;
    isDone = false;

}

void Ani_TrieDelete::updateAnimations(float deltaTime){
    if(isDone) return;
    elapsed_time+=deltaTime;
    float t = elapsed_time / duration;
    if (t>=1.0f){
        isDone = true;
        Trie_Scene::ani = Updating;
    }
}

 // Trie Search

Ani_TrieSearch::Ani_TrieSearch() : Animations(0) {
    isDone = true;
    doneSearch = false;
 }

Ani_TrieSearch::Ani_TrieSearch(float duration ): Animations(duration) {
}

void Ani_TrieSearch::play(){
    elapsed_time = 0;
    isDone = false;
    
}

void Ani_TrieSearch::setKey(const string word){
    key = word;
}
void Ani_TrieSearch::updateAnimations(float deltaTime){
    if(isDone) return;
    elapsed_time+=deltaTime;
    float t = elapsed_time / duration;
    //std::cout<< t<<"\n";
    if(Trie_Scene::ani_state==Forward && !doneSearch) t=1.0f;
    if (t>=1.0f && !doneSearch){
        isDone = true;
        Trie_Scene::ani = None;
    }
    else if (t >=1.0f && doneSearch ) {

        TrieNodePrimary* tmp = Trie_Scene::proot;
        bool found = true;  
        std::cout<< "search for " << key << "\n";
        for (char ch : key) {
            if (tmp->children.find(ch) != tmp->children.end()) {
                tmp = tmp->children[ch];  
                if(!tmp->isEndOfWord) tmp->SetNullHighLight();  
            } 
            
            else {
                found = false;
                break;
            }
        }

        doneSearch=false;
        isDone = true;
        Trie_Scene::ani = None;
    }
}
void Ani_TrieSearch::setDone(bool Done){
    doneSearch= Done;
}
//Trie Update

Ani_TrieUpdate::Ani_TrieUpdate() : Animations(0) {
    isDone = true;
 }


void Ani_TrieUpdate::play(){
    elapsed_time = 0;
    isDone = false;

}
void Ani_TrieUpdate::updateAnimations(float deltaTime){
    if(isDone || Trie_Scene::ani != Updating) return;
    elapsed_time+=deltaTime;
    float t = elapsed_time / duration;
    if (t>=1.0f){
        isDone = true;
        Trie_Scene::ani = None;
    }
}

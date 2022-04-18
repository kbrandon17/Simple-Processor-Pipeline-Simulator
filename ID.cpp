#ifndef Stageh
#define Stageh
#include "Stage.h"
#endif
class ID: public Stage {
    public:
    InstructionList* queue;
    DependencyList* deplist;

    ID(int pipelines, DependencyList* ndeplist) : Stage(pipelines){
        queue = new InstructionList();
        deplist = ndeplist;
    }


    void run(Stage* ifObj){
        while ((queue->length + list->length) <= size){
            Instruction* poppedIns = ifObj->popReadyIns();
            if (poppedIns == NULL) {break;}
            queue->insert(poppedIns);
        }
        Instruction* item;
        while(true){
            item = queue->popReadyIns(deplist, size);
            if(item == NULL){break;}
            list->insert(item);
        }
    }
};
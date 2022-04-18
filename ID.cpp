#include "Stage.h"
class ID: public Stage {

    InstructionList* queue;
    ID(){

    }


    void run(Stage* ifObj, DependencyList* depList){
        while ((queue->length + list->length) <= size){
            queue->insert(ifObj->popReadyIns());
        }
        Instruction* item;
        while(true){
            item = queue->popReadyIns(depList, size);
            if(item == NULL){break;}
            list->insert(item);
        }
    }
};
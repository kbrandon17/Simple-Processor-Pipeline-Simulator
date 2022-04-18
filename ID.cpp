#include "Stage.h"
class ID: public Stage {

    InstructionList* queue;
    ID(){

    }


    void run(Stage* ifObj, DependencyList* depList){
        while ((queue->length + list->length) <= size){
            Instruction* poppedIns = ifObj->popReadyIns();
            if (poppedIns == NULL) {break;}
            queue->insert(poppedIns);
        }
        Instruction* item;
        while(true){
            item = queue->popReadyIns(depList, size);
            if(item == NULL){break;}
            list->insert(item);
        }
    }
};
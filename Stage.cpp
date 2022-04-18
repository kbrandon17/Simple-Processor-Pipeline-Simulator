#include "InstructionList.h"
#include "DependencyList.h"
#include "Instruction.h"
#include "list"

class Stage {
    InstructionList* list;
    int size;



    Stage(int pipelines){
       list = new InstructionList();
       size = pipelines;
    }

    void addInstruction(Instruction* ins){
        list->insert(ins);
    }

    virtual void run(Stage* stage){
        while (list->length <= size){
            list->insert(stage->popReadyIns());
        }
        return;
    }


    Instruction* popReadyIns(){
        return popReadyIns(NULL);
    }
    Instruction* popReadyIns(DependencyList* deplist) {
        return list->popReadyIns(deplist, size);
    }



/*        Instruction* curr = list->getHead();
        if(curr == NULL) {return NULL;}
        Instruction* next = curr->next;
        list->setHead(next);
        if (next == NULL) {list->setTail(NULL);}
        curr->next = NULL;
        return curr;*/
};
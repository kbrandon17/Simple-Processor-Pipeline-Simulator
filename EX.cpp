#ifndef Stageh
#define Stageh
#include "Stage.h"
#endif
#ifndef InsList
#define InsList
#include "InstructionList.h"
#endif
class EX: public Stage {
    public:
    InstructionList* queue;
    //1 of each type of ex processor i.e. only one of each instruction type per cycle
    bool type1Done;
    bool type2Done;
    bool type3Done;
    DependencyList* deplist;


    EX(int pipelines, DependencyList* ndeplist) : Stage(pipelines){
        type1Done = false;
        type2Done = false;
        type3Done = false;
        queue = new InstructionList();
        deplist = ndeplist;
    }

    void clearTypesDone(){
        type1Done = false;
        type2Done = false;
        type3Done = false;
        return;
    }

    void run(Stage* id, bool* jammed){
        clearTypesDone();
        while (queue->length + list->length <= size){
            Instruction* poppedIns = id->popReadyIns();
            if (poppedIns == NULL) {break;}
            queue->insert(poppedIns);
        }
        while(true){
            Instruction* head = queue->getHead();
            if(head == NULL){break;}
            int type = head->getType();
            if(type == 1 && type1Done == false){
                list->insert(queue->pop(0));
                type1Done = true;
            } else if (type == 2 && type2Done == false){
                list->insert(queue->pop(0));
                type2Done = true;
            } else if (type == 3 && type3Done == false){
                list->insert(queue->pop(0));
                type3Done = true;
                *jammed = false;
            } else if (type == 4 || type == 5){
                list->insert(queue->pop(0));
            } else {
                break;
            }
        }
    }

};
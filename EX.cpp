#include "Stage.h"
#include "InstructionList.h"
class EX: public Stage {
    InstructionList* queue;
    //1 of each type of ex processor i.e. only one of each instruction type per cycle
    bool type1Done;
    bool type2Done;
    bool type3Done;
    EX(){}
    void clearTypesDone(){
        type1Done = false;
        type2Done = false;
        type3Done = false;
        return;
    }

    void run(Stage* id, bool* jammed){
        clearTypesDone();
        while (queue->length + list->length <= size){
            queue->insert(id->popReadyIns());
        }
        while(true){
            int type = queue->getHead()->getType();
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
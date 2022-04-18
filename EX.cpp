#include "Stage.h"
#include "InstructionList.h"
class EX: public Stage {
    InstructionList* queue;
    //1 of each type of ex processor i.e. only one of each instruction type per cycle
    bool type1Done;
    bool type2Done;
    bool type3Done;
    bool type4Done;
    bool type5Done;
    EX(){}
    void clearTypesDone(){
        type1Done = false;
        type2Done = false;
        type3Done = false;
        type4Done = false;
        type5Done = false;
        return;
    }

    bool run(Stage* id){
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
            } else if (type == 4 || type == 5){
                list->insert(queue->pop(0));
            } else {
                break;
            }
        }
    }

};
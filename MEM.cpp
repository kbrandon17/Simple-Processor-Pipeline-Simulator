#include "Stage.h"
#include "InstructionList.h"
class MEM: public Stage {
    InstructionList* queue;
    //1 of each type of ex processor i.e. only one of each instruction type per cycle
    bool type4Done;
    bool type5Done;
    MEM(){}
    void clearTypesDone(){
        type4Done = false;
        type5Done = false;
        return;
    }

    void run(Stage* id, bool* jammed){
        clearTypesDone();
        while (queue->length + list->length <= size){
            queue->insert(id->popReadyIns());
        }
        while(true){
            int type = queue->getHead()->getType();
            if(type == 4 && type4Done == false){
                list->insert(queue->pop(0));
                type4Done = true;
            } else if (type == 5 && type5Done == false){
                list->insert(queue->pop(0));
                type5Done = true;
            } else if (type == 1 || type == 2 || type == 3){
                list->insert(queue->pop(0));
            } else {
                break;
            }
        }
    }

};
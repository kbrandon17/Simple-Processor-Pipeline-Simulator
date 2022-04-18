#include "Stage.h"
class WB : public Stage {


    WB(int pipelines) : Stage(pipelines){}
    int run(Stage* stage){
        int dispatched = 0;
        while (list->length <= size){
            Instruction* poppedIns = stage->popReadyIns();
            if (poppedIns == NULL) {break;}
            list->insert(poppedIns);
        }
        while (Instruction* ins = popReadyIns()){
            if (ins == NULL){break;}
            delete ins;
            dispatched++;
        }
        return dispatched;
    }
};
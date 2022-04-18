#include "Stage.h"
class WB: public Stage {


    WB(int){}
    int run(Stage* stage){
        int dispatched = 0;
        while (list->length <= size){
            list->insert(stage->popReadyIns());
        }
        while (Instruction* ins = popReadyIns()){
            if (ins == NULL){break;}
            delete ins;
            dispatched++;
        }
        return dispatched;
    }
};
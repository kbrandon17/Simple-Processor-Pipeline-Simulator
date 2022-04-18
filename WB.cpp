#ifndef Stageh
#define Stageh
#include "Stage.h"
#endif

class WB: public Stage {


    WB(int){}
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
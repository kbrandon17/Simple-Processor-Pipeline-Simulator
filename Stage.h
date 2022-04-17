#include "Instruction.h"
class Stage {

    public:
    Stage();
    Instruction* popReadyIns();
    void run();
};
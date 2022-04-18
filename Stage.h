#include "Instruction.h"
#include "InstructionList.h"
#include "DependencyList.h"

class Stage {
    
    public:
    InstructionList* list;
    int size;
    Stage();
    Instruction* popReadyIns();
    void run();
    void addInstruction(Instruction* ins);
    bool checkDependency(Instruction* ins, DependencyList* deplist);
    Instruction* popReadyIns(DependencyList* deplist);
};
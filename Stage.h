#ifndef Ins
#define Ins
#include "Instruction.h"
#endif
#ifndef InsList
#define InsList
#include "InstructionList.h"
#endif
#ifndef DepList
#define DepList
#include "DependencyList.h"
#endif

class Stage {

    public:
    InstructionList* list;
    int size;
    Stage(int);
    //void run(Stage*);
    void addInstruction(Instruction* ins);
    Instruction* popReadyIns(DependencyList* deplist);
    Instruction* popReadyIns();
};
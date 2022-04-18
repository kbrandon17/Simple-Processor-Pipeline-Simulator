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
    Instruction* popReadyIns();
    void run();
    void addInstruction(Instruction* ins);
    bool checkDependency(Instruction* ins, DependencyList* deplist);
    Instruction* popReadyIns(DependencyList* deplist);
};
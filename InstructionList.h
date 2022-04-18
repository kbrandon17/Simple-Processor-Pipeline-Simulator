#ifndef Ins
#define Ins
#include "Instruction.h"
#endif
#ifndef DepList
#define DepList
#include "DependencyList.h"
#endif

class InstructionList{
    public:
    Instruction* head;
    Instruction* tail;
    int length;

    InstructionList();
    void insert(Instruction* ins);
    Instruction* pop(int index);
    bool checkDependency(Instruction* ins, DependencyList* deplist);
    Instruction* popReadyIns(DependencyList* deplist, int size);
    Instruction* getHead();
    Instruction* getTail();
    void setHead(Instruction* head2);
    void setTail(Instruction* tail2);

};
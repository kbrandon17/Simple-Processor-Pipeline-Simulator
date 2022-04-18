#include "Instruction.h"

class InstructionList{
    public:
    Instruction* head;
    Instruction* tail;
    int length;

    void insert(Instruction* ins);

    Instruction* pop(int index);

    Instruction* getHead();

    Instruction* getTail();
    Instruction* setHead(Instruction* head2);
    
    Instruction* setTail(Instruction* tail2);
    Instruction* popReadyIns(DependencyList* deplist, int size);
    bool checkDependency(Instruction* ins, DependencyList* deplist);


};
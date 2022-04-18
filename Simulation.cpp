#include "WB.h"
#include "MEM.h"
#include "EX.h"
#include "ID.h"
#include "IF.h"
#include <fstream>

using std::string;

class Simulation {
string startIns;
bool branchJammed;
int insDispatched;
int insCount;
int cycles;
IF* ifObj;
ID* idObj;
EX* exObj;
MEM* memObj;
WB* wbObj;

void run(char* filePath, int startInstruction, int instructionCount, int pipelineWidth){
    string line;
    std::ifstream traceFile(filePath);
    traceFile.open(filePath);
    for (int i = 0; i <= startInstruction; i++) {
    getline(traceFile, line);
}
    while(insDispatched != insCount){
        getline(traceFile, line);
        insDispatched += wbObj->run(memObj);
        memObj->run(exObj);
        exObj->run(idObj);
        idObj->run(ifObj);
        ifObj->run(line, &branchJammed);
        cycles++;
    }

}

Simulation(){

branchJammed = false;

}

};
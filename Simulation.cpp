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

void run(){
    while(insDispatched != insCount){
        insDispatched += wbObj->run(memObj);
        memObj->run(exObj);
        exObj->run(idObj);
        idObj->run(ifObj);
        ifObj->run(&branchJammed);
        cycles++;
    }

}

Simulation(char* filePath, int startInstruction, int instructionCount, int pipelineWidth){

branchJammed = false;
int count;
string line;
std::ifstream traceFile(filePath);
traceFile.open(filePath);
for (int i = 0; i <= startInstruction; i++) {
    getline(traceFile, line);
}
while(count < instructionCount) {
    //run everything
}
}

};
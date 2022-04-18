#include "WB.h"
#include "MEM.h"
#include "EX.h"
#include "ID.h"
#include "IF.h"
#include <fstream>

using std::string;
using std::list;

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
DependencyList* deplist;

void tokenize(string s, string del, list<string> newList) {
    int start = 0;
    int end = s.find(del);
    while (end != -1) {
        newList.push_back(s.substr(start, end - start));
        start = end + del.size();
        end = s.find(del, start);
    }
    newList.push_back(s.substr(start, end - start));
}

void run(char* filePath, int startInstruction, int instructionCount){
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
        exObj->run(idObj, &branchJammed);
        idObj->run(ifObj, deplist);
        list<string> listIns;
        tokenize(line, ",", listIns);
        if(cycles == 0) {
            startIns = listIns.front();
        }
        ifObj->run(listIns, &branchJammed);
        cycles++;
    }

}

Simulation(int pipelineWidth){

    branchJammed = false;
    insDispatched = 0;
    insCount = 0;
    cycles = 0;
    ifObj = new IF(pipelineWidth);
    idObj = new ID(pipelineWidth);
    exObj = new EX(pipelineWidth);
    memObj = new MEM(pipelineWidth);
    wbObj = new WB(pipelineWidth);
    deplist = new DependencyList();
}

};
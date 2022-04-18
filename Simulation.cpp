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
        exObj->run(idObj, &branchJammed);
        idObj->run(ifObj);
        list<string> listIns;
        tokenize(line, ",", listIns);
        if(cycles == 0) {
            startIns = listIns.front();
        }
        ifObj->run(listIns, &branchJammed);
        cycles++;
    }

}

Simulation(){

    string startIns;
    bool branchJammed = false;
    int insDispatched = 0;
    int insCount = 0;
    int cycles = 0;
    IF* ifObj;
    ID* idObj;
    EX* exObj;
    MEM* memObj;
    WB* wbObj;

}

};
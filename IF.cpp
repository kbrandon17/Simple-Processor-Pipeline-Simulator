#include "Stage.h"
#include <string>


using std::string;

class IF: public Stage {

    IF(list<string> ins) {

    }

    void run(list<string> ins, bool* branchJammed) {
        string pc = ins.front();
        ins.pop_front();
        int type = stoi(ins.front());
        if(type == 3) {
            *branchJammed = true;
        }
        ins.pop_front();
        list<string> dep;
        while (!ins.empty()) {
            dep.push_back(ins.front());
            ins.pop_front();
        }
        Instruction* newInstruction = new Instruction(type, pc, dep);
    }
};
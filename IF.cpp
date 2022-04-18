#include "Stage.h"
#include <string>


using std::string;

class IF: public Stage {

    IF(list<string> ins) {
        string pc = ins.front();
        ins.pop_front();
        int type = stoi(ins.front());
        ins.pop_front();
        list<string> dep;
        while (!ins.empty()) {
            dep.push_back(ins.front());
            ins.pop_front();
        }
        Instruction* newInstruction = new Instruction(type, pc, dep);
    }
    void run(bool* branchJammed);
};
#include <string>
#include <list>

using std::string;
using std::list;

class Instruction {
    public:
    int length;
    int type;
    string pc;
    list<string> dependencies;
    string nextStage;
    Instruction* next;

    int getType(){
        return type;
    }

    Instruction(int ntype, string insPc, list<string> dep) {
        type = ntype;
        pc = insPc;
        dependencies = dep;
        nextStage = 2;
        next = NULL;
    }

    
};
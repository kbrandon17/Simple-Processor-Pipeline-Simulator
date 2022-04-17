#include <string>
#include <list>

using std::string;
using std::list;

class Instruction {
    int length;
    int type;
    string pc;
    list<string> dependencies;
    string nextStage;
    Instruction* next;

    int getType(){
        return type;
    }

    
};
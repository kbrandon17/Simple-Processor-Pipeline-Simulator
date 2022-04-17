#include <string>

using std::string;

class Instruction {
    int type;
    string pc;
    string dependencies[4];
    string nextStage;
    Instruction* next;

    int getType(){
        return type;
    }

    stri
};
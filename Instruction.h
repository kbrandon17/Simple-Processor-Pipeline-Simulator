#include <string>

using std::string;

class Instruction{
    int getType();
    string getDependencies();
    string getNextStage();
    string getPC();
    Instruction* next();
    Instruction();
    
};
#include <string>
#include <list>

using std::list;
using std::string;

class Instruction{
    public:

    list<string> dependencies;
    int getType();
    //string getDependencies();
    //string getNextStage();
    //string getPC();
    Instruction* next;
    Instruction(int type, string insPc, list<string> dep);
    
};
using std::string;
class Simulation {

public:
bool branchJammed;

void run(char* filePath, int startInstruction, int instructionCount);

Simulation(int);
void tokenize(string s, string del, std::list<string> newList);

};
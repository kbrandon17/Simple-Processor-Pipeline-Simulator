class Simulation {
public:
bool branchJammed;

void run();

Simulation(char* filePath, int startInstruction, int instructionCount, int pipelineWidth);

};
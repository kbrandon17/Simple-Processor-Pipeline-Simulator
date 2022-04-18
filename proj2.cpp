#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <string.h>
#include <list>
#include "Simulation.h"

using std::string;

int main(int argc, char** argv) {
    char filePath[30];
    

    if (argc != 5) {
        printf("Incorrect number of arguments provided. Exiting now!\n");
        exit(1);
    }

    strcpy(filePath, argv[1]);
    strcat(filePath, ".txt");
    int startInstruction = atoi(argv[2]);
    int instructionCount = atoi(argv[3]); 
    int pipelineWidth = atoi(argv[4]);
    


    Simulation(filePath, startInstruction, instructionCount, pipelineWidth);

    return 0;
}
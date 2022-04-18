#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <string.h>
#include <list>
#include "Simulation.h"

using std::string;

void isNumber(char number[])
{
    for (int i = 0; number[i] != 0; i++)
    {
        if (!isdigit(number[i])) {
            printf("All non-filepath variables are not integers, exiting now!");
            exit(1);
        }
    }
}

int main(int argc, char** argv) {
    char filePath[30];
    
    if (argc != 5) {
        printf("Incorrect number of arguments provided. Exiting now!\n");
        exit(1);
    }
    for (int i = 2; i < 5; i++) {
        isNumber(argv[i]);
    }

    strcpy(filePath, argv[1]);
    strcat(filePath, ".txt");
    int startInstruction = atoi(argv[2]);
    int instructionCount = atoi(argv[3]); 
    int pipelineWidth = atoi(argv[4]);
    
    Simulation* sim;

    sim->run(filePath, startInstruction, instructionCount, pipelineWidth);

    return 0;
}
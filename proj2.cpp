#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <string.h>
#include <list>

using std::string;

int main(int argc, char** argv) {
    char curr[18];
    if (argc != 5) {
        printf("Incorrect number of arguments provided. Exiting now!\n");
        exit(1);
    }
    strcpy(curr, argv[1]);
    printf("%s\n", curr);
    // int startInstruction = atoi(argv[2]);
    // int instructionCount = atoi(argv[3]); 
    // int pipelineWidth = atoi(argv[4]);

    return 0;
}
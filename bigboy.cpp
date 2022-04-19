#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <list>
#include <set>
#include <fstream>
#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>
#include <iterator>


using std::string;
using std::list;
using std::stoul;
using std::set;


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

class DependencyList{
    public:
    long unsigned int start;
    set<string>* dependencyList;

    DependencyList(){
        dependencyList = new set<string>;
        start = 0;
    }

    void setStart (string startStr){
        start = stoul("0x" + startStr, nullptr, 16);
    }

    void add(string dependency){
        dependencyList->insert(dependency);
    }
    
    int search(string dependency){
        return dependencyList->count(dependency);
    }

};

class InstructionList{
    public:
    Instruction* head;
    Instruction* tail;
    int length;

    InstructionList(){
        head = NULL;
        tail = NULL;
        length = 0;
    }

    void insert(Instruction* ins){
        if (ins == NULL){return;}
        length++;
        if (tail == NULL){
            head = ins;
            tail = ins;
            return;
        } else {
            tail->next = ins;
            tail = ins;
            return;
        }
    }

    Instruction* pop(int index) {
        Instruction* curr = head;
        Instruction* last = NULL;
        if (curr == NULL) {return NULL;}
        for(int i=0; i<index; i++){
            last = curr;
            curr = curr->next;
            if (curr == NULL) {return NULL;}
        }
        if(curr==tail) {
            tail = last;
        }
        if (curr == head){
            head = curr->next;
        }
        curr->next = NULL;
        length--;
        return curr;
    }

    bool checkDependency(Instruction* ins, DependencyList* deplist){
        for(const auto& dep : ins->dependencies){
            string hexins = "0x" + dep;
           // if (stoul("0x" + dep, nullptr, 16) >= deplist->start){
               printf("\ndependency list is: \n");
               print(deplist->dependencyList);
               printf("\ndependency is: \n");
               printf("%s", dep.c_str());
                if (deplist->search(dep) == 1){
                    return false;
                }
         //   }
        }
        return true;
    }
    void print(std::set<string> const *s)
{
    std::copy(s->begin(),
            s->end(),
            std::ostream_iterator<string>(std::cout, " "));
}

    Instruction* popReadyIns(DependencyList* deplist, int size) {
        Instruction* popped = NULL;
        if (deplist != NULL && getHead() != NULL){
            //print(deplist->dependencyList);
            bool result = checkDependency(getHead(), deplist);
            if (result){
                popped = pop(0);
            }
            /*bool result = false;
            Instruction* curr = NULL;
            int i;
            for(i=0; i<size; i++){
                if(i=0){
                    curr = getHead();
                } else {
                    curr = curr->next;
                }
                result = checkDependency(curr, deplist);
                if(result == true) {
                    popped = pop(i);
                }
            }*/

        } else {
            popped = pop(0);
        }

        return popped;
    }

    Instruction* getHead(){
        return head;
    }

    Instruction* getTail(){
        return tail;
    }

    void setHead(Instruction* head2){
        head = head2;
    }
    
    void setTail(Instruction* tail2){
        tail = tail2;
    }

};

class Stage {
    public:
    InstructionList* list;
    int size;



    Stage(int pipelines){
       list = new InstructionList();
       size = pipelines;
    }

    void addInstruction(Instruction* ins){
        list->insert(ins);
    }

    // virtual void run(Stage* stage){
    //     while (list->length <= size){
    //         list->insert(stage->popReadyIns());
    //     }
    //     return;
    // }


    Instruction* popReadyIns(){
        return popReadyIns(NULL);
    }
    
    Instruction* popReadyIns(DependencyList* deplist) {
        return list->popReadyIns(deplist, size);
    }



/*        Instruction* curr = list->getHead();
        if(curr == NULL) {return NULL;}
        Instruction* next = curr->next;
        list->setHead(next);
        if (next == NULL) {list->setTail(NULL);}
        curr->next = NULL;
        return curr;*/
};

class WB: public Stage {
    public:
    WB(int pipelines) : Stage(pipelines){}
    int run(Stage* stage){
        int dispatched = 0;
        while (list->length < size){
            Instruction* poppedIns = stage->popReadyIns();
            if (poppedIns == NULL) {break;}
            list->insert(poppedIns);
        }
        while (Instruction* ins = popReadyIns()){
            if (ins == NULL){break;}
            delete ins;
            dispatched++;
        }
        return dispatched;
    }
};

class MEM: public Stage {
    public:
    InstructionList* queue;
    //1 of each type of ex processor i.e. only one of each instruction type per cycle
    bool type4Done;
    bool type5Done;
    DependencyList* deplist;

    MEM(int pipelines, DependencyList* ndeplist) : Stage(pipelines){
        type4Done = false;
        type5Done = false;
        queue = new InstructionList();
        deplist = ndeplist;
    }
    void clearTypesDone(){
        type4Done = false;
        type5Done = false;
        return;
    }

    void run(Stage* id){
        clearTypesDone();
        while (queue->length + list->length < size){
            Instruction* poppedIns = id->popReadyIns();
            if (poppedIns == NULL) {break;}
            queue->insert(poppedIns);
        }
        while(true){
            Instruction* head = queue->getHead();
            if(head == NULL){break;}
            int type = head->getType();
            if(type == 4 && type4Done == false){
                deplist->add(head->pc);
                list->insert(queue->pop(0));
                type4Done = true;
            } else if (type == 5 && type5Done == false){
                deplist->add(head->pc);
                list->insert(queue->pop(0));
                type5Done = true;
            } else if (type == 1 || type == 2 || type == 3){
                list->insert(queue->pop(0));
            } else {
                break;
            }
        }
    }

};

class IF: public Stage {
    public:
    DependencyList* deplist;
    IF(int pipelines, DependencyList* Ndeplist) : Stage(pipelines) {
        deplist = Ndeplist;
    }

    string run(std::list<string> ins, int* branchJammed) {
        string pc = ins.front();

        ins.pop_front();
        int type = stoi(ins.front());
        if(type == 3) {
            *branchJammed = 1;
        }
        ins.pop_front();
        std::list<string> dep;
        while (!ins.empty()) {
            dep.push_back(ins.front());
            ins.pop_front();
        }
        Instruction* newInstruction = new Instruction(type, pc, dep);
        if(list->length < size) {
            addInstruction(newInstruction);
        }
        /*if(deplist->search(pc) == 0) {
            pc = "";
        }*/
        return pc;   
    }
};

class ID: public Stage {
    public:
    InstructionList* queue;
    DependencyList* deplist;

    ID(int pipelines, DependencyList* ndeplist) : Stage(pipelines){
        queue = new InstructionList();
        deplist = ndeplist;
    }


    void run(Stage* ifObj){
        /*while ((queue->length + list->length) < size){
            Instruction* poppedIns = ifObj->popReadyIns();
            if (poppedIns == NULL) {break;}
            queue->insert(poppedIns);
        }*/
        Instruction* item;
        while((queue->length + list->length) < size){
            //item = queue->popReadyIns(deplist, size);
            item = ifObj->popReadyIns();
            if(item == NULL){break;}
            list->insert(item);
            deplist->add(item->pc);
        }
    }
};

class EX: public Stage {
    public:
    InstructionList* queue;
    //1 of each type of ex processor i.e. only one of each instruction type per cycle
    bool type1Done;
    bool type2Done;
    bool type3Done;
    DependencyList* deplist;
    DependencyList* depchecklist;


    EX(int pipelines, DependencyList* ndeplist, DependencyList* ndepchecklist) : Stage(pipelines){
        type1Done = false;
        type2Done = false;
        type3Done = false;
        queue = new InstructionList();
        deplist = ndeplist;
        depchecklist = ndepchecklist;
    }

    void clearTypesDone(){
        type1Done = false;
        type2Done = false;
        type3Done = false;
        return;
    }

    void run(Stage* id, int* jammed){
        clearTypesDone();
        while (queue->length + list->length < size){
            Instruction* poppedIns = id->popReadyIns(depchecklist);
            if (poppedIns == NULL) {break;}
            queue->insert(poppedIns);
        }
        while(true){
            Instruction* head = queue->getHead();
            if(head == NULL){break;}
            int type = head->getType();
            if(type == 1 && type1Done == false){
                deplist->add(head->pc);
                list->insert(queue->pop(0));
                type1Done = true;
            } else if (type == 2 && type2Done == false){
                deplist->add(head->pc);
                list->insert(queue->pop(0));
                type2Done = true;
            } else if (type == 3 && type3Done == false){
                deplist->add(head->pc);
                list->insert(queue->pop(0));
                type3Done = true;
                *jammed = 2;
            } else if (type == 4 || type == 5){
                list->insert(queue->pop(0));
            } else {
                break;
            }
        }
    }

};

class Simulation {
    public:
string startIns;
int branchJammed;
int insDispatched;
int insCount;
int cycles;
IF* ifObj;
ID* idObj;
EX* exObj;
MEM* memObj;
WB* wbObj;
DependencyList* deplist;
DependencyList* tempdeplist;

list<string> tokenize(string s, string del) {
    list<string> newList;
    int start = 0;
    int end = s.find(del);
    while (end != -1) {
        newList.push_back(s.substr(start, end - start));
        start = end + del.size();
        end = s.find(del, start);
    }
    newList.push_back(s.substr(start, end - start));
    return newList;
}

void run(char* filePath, int startInstruction, int instructionCount){
    FILE* fp = fopen(filePath, "r");
    if(fp == NULL) {
        printf("Incorrect file name given!");
        exit(1);
        }
    char* line;
    size_t len = 0;

    for (int i = 1; i < startInstruction; i++) {
        getline(&line, &len, fp);
}
    insCount = instructionCount;
    list<string> listIns;
    string lastPC;
    printf("insDispatched: %d\ninsCount: %d\n", insDispatched, insCount);
    while(insDispatched < insCount){
        int deplistsize = tempdeplist->dependencyList->size();
        for(int i=0; i < deplistsize; i++){
            deplist->dependencyList->erase(*(tempdeplist->dependencyList->begin()));
            tempdeplist->dependencyList->erase(tempdeplist->dependencyList->begin());
        }
        deplist->dependencyList->insert(tempdeplist->dependencyList->begin(), tempdeplist->dependencyList->end());
        tempdeplist->dependencyList->clear();
        insDispatched += wbObj->run(memObj);
        printf("insDispatched: %d\n", insDispatched);
        memObj->run(exObj);
        exObj->run(idObj, &branchJammed);
        idObj->run(ifObj);
        /*if(!lastPC.empty()) {
            deplist->dependencyList->erase(lastPC);
            lastPC = "";
        }*/
        if(branchJammed == 3 && ifObj->list->length < ifObj->size) {
            getline(&line, &len, fp);
            string strline(line);
            strline.erase(std::remove(strline.begin(), strline.end(), '\n'), strline.end());
            listIns = tokenize(strline, ",");
            string test = ifObj->run(listIns, &branchJammed);
            //deplist->add(test);
        }
        if (branchJammed == 2) {
            branchJammed = 3;
        }
        
        if(cycles == 0) {
            deplist->setStart(listIns.front());
        }
        printf("\n%d\n", cycles);
        cycles++;
    }

}

Simulation(int pipelineWidth){

    branchJammed = 3;
    insDispatched = 0;
    insCount = 0;
    cycles = 0;
    tempdeplist = new DependencyList();
    deplist = new DependencyList();
    ifObj = new IF(pipelineWidth, deplist);
    idObj = new ID(pipelineWidth, deplist);
    exObj = new EX(pipelineWidth, tempdeplist, deplist);
    memObj = new MEM(pipelineWidth, tempdeplist);
    wbObj = new WB(pipelineWidth);
    
}

};


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
    int startInstruction = atoi(argv[2]);
    int instructionCount = atoi(argv[3]); 
    int pipelineWidth = atoi(argv[4]);
    Simulation* sim = new Simulation(pipelineWidth);
    sim->run(filePath, startInstruction, instructionCount);

    return 0;
}
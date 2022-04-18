#include "Instruction.h"
#include "DependencyList.h"

class InstructionList{
    Instruction* head;
    Instruction* tail;
    int length;

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
            if (deplist->search(dep) == 0){
                return false;
            }
        }
        return true;
    }

    Instruction* popReadyIns(DependencyList* deplist, int size) {
        Instruction* popped = NULL;
        if (deplist != NULL && getHead() != NULL){
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

    Instruction* setHead(Instruction* head2){
        head = head2;
    }
    
    Instruction* setTail(Instruction* tail2){
        tail = tail2;
    }

};
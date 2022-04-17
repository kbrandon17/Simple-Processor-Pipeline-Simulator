#include "Instruction.h"

class InstructionList{
    Instruction* head;
    Instruction* tail;
    int length;

    void insert(Instruction* ins){
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
        return curr;
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
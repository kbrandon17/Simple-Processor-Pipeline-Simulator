#ifndef Stageh
#define Stageh
#include "Stage.h"
#endif
class MEM: public Stage {

    public:
    MEM(int, DependencyList*);
    void run(EX*);
};
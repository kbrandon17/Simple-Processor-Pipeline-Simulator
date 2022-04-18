#ifndef Stageh
#define Stageh
#include "Stage.h"
#endif
class EX: public Stage {

    public:
    EX(int, DependencyList*);
    void run(Stage*, bool*);
    void clearTypesDone();

};
#ifndef Stageh
#define Stageh
#include "Stage.h"
#endif
class ID: public Stage {

    public:
    ID(int, DependencyList*);
    void run(Stage*);
};
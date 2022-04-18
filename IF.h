#ifndef Stageh
#define Stageh
#include "Stage.h"
#endif
class IF: public Stage {

    public:
    IF();
    void run(std::list<string>, bool*);
};
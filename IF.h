#include "Stage.h"
class IF: public Stage {

    public:
    IF(int);
    void run(std::list<string>, bool*);
};
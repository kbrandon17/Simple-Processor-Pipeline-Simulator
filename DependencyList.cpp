#include <string>
#include <set>
using std::string;
using std::set;
using std::stoul;

class DependencyList{
    int start;
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
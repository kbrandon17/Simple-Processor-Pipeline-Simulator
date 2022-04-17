#include <string>
#include <set>
using std::string;
using std::set;

class DependencyList{
    string start;
    set<string>* dependencyList;

    DependencyList(string start2){
        start=start2;
        dependencyList = new set<string>;
    }

    void add(string dependency){
        dependencyList->insert(dependency);
    }
    
    int search(string dependency){
        return dependencyList->count(dependency);
    }

};
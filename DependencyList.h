#include <string>
#include<set>
using std::string;
using std::set;

class DependencyList{
    private:
    set<string>* dependencyList;
    public:
    long unsigned int start;

    DependencyList();

    void add(string dependency);
    
    int search(string dependency);

};
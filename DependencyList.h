#include <string>
#include<set>
using std::string;
using std::set;

class DependencyList{
    public:
    //private:
    set<string>* dependencyList;
    //public:
    long unsigned int start;

    DependencyList();

    void setStart (string startStr);

    void add(string dependency);
    
    int search(string dependency);

};
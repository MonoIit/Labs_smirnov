#include <iostream>
#include <stack>
#include <list>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "pipe.h"
#include "KC.h"
#include "tools.h" 

using namespace std;

class GTN
{
    int v;

    void topologicalSortUtil(int v, bool visited[], stack<int> &Stack);
    
    list<int> *adj;
    stack<vector<int>> storage;
public:
    GTN(int size);
    void expandGTN();
    void addConnection(unordered_map<int, Pipe> &, unordered_map<int, KC> &);
    void removeConnection(unordered_map<int, Pipe> &, unordered_map<int, KC> &);
    void displayConnections(unordered_map<int, Pipe> &, unordered_map<int, KC> &);
    void topologicalSort();
};
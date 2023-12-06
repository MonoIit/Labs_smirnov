#include <iostream>
#include <stack>
#include <list>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "pipe.h"
#include "KC.h"
#include "tools.h"
#include "GTN.h"

int chose_kc(unordered_set<int> &res, unordered_map<int, KC>& KCs, int KCid = -1)
{
    int KCID;

    for (auto &[kId, k] : KCs)
    {
        if (k.getId() != KCid)
        {
            res.insert(kId);
        }
    }

    for (int id : res)
    {
        cout << KCs[id];
    }

    cout << "Choose KC id" << endl;
    input_id(KCID, res);
    return KCID;
}

GTN::GTN(int size = 0)
{
    this->v = size;
    adj = new list<int>[v];
}

void GTN::expandGTN()
{
    this->v = v + 1;

}

void GTN::addConnection(unordered_map<int, Pipe>& pipes, unordered_map<int, KC>& KCs)
{


    unordered_set<int> result;
    cout << "Enter diameter" << endl;
    int diameter;
    diameter = input_diameter();
    for (auto&[pId, p] : pipes)
    {
        if (p.Diameter == diameter && p.connect_status != 1)
        {
            result.insert(pId);
        }
    }
    
    for (int id : result)
    {
        cout << pipes[id];
    }

    cout << "Choose pipe id" << endl;
    int pipeId;
    input_id(pipeId, result);
    result.clear();

    int KCfromId = chose_kc(result, KCs);
    result.clear();
    int KCtoId = chose_kc(result, KCs, KCfromId);
    if (KCfromId != KCtoId)
    {   
        KCs[KCfromId].connections += 1;
        KCs[KCtoId].connections += 1;
        pipes[pipeId].connect_from = KCfromId;
        pipes[pipeId].connect_to = KCtoId;
        pipes[pipeId].connect_status = 1;
    }
    else {
        cout << "error" << endl;
    }
}

void GTN::removeConnection(unordered_map<int, Pipe>& pipes, unordered_map<int, KC>& KCs)
{
    vector<int> res;
    for (auto&[pId, p] : pipes)
    {   
        if (p.connect_status == 1)
        {
            cout << p;
            res.push_back(pId);
        }
    }
    cout << "Enter pipe id" << endl;
    int id;
    input_id(id, res);
    KCs[pipes[id].connect_from].connections -= 1;
    KCs[pipes[id].connect_to].connections -= 1;
    pipes[id].connect_from = -1;
    pipes[id].connect_to = -1;
    pipes[id].connect_status = 0;
}

void GTN::displayConnections(unordered_map<int, Pipe> &pipes, unordered_map<int, KC> &KCs)
{
    bool flag = false;
    for (auto[pId, p] : pipes)
    {
        if (p.connect_status == 1)
        {
            cout << "Pipe's ID: " << pId << endl;
            cout << "Station's ID from: " << p.connect_from << endl;
            cout << "Station's ID to: " << p.connect_to << endl;
            cout << "Status: " << ((p.Status == true) ? "repair " : "work ") << endl;
            flag = true;
        }
    }
    if (flag == false)
        cout << "No connections" << endl;
}

void GTN::topologicalSortUtil(int v, bool visited[], stack<int> &Stack)
{
    visited[v] = true;
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            topologicalSortUtil(*i, visited, Stack);

    Stack.push(v);
}

void GTN::topologicalSort()
{
    stack<int> Stack;

    bool *visited = new bool[v];
    for (int i = 0; i < v; i++)
        visited[i] = false;


    for (int i = 0; i < v; i++)
        if (visited[i] == false)
            topologicalSortUtil(i, visited, Stack);
    
    while(Stack.empty() == false)
    {
        cout << Stack.top() << " ";
        Stack.pop();
    }
}




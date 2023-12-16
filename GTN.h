#pragma once
#include <iostream>
#include <algorithm>
#include <set>
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
    set<int> CreateIndexes(const unordered_map<int, Pipe> &pipes, const unordered_map<int, KC> &KCs);
    unordered_map<int, int> CreateReverseAdjMatrix(const unordered_map<int, Pipe> &pipes, const unordered_map<int, KC> &KCs);
    bool created = false;
    void action_pipes(unordered_set<int>& IDS);
    void action_KCs(unordered_set<int> &IDS);
    void narrow_set_pipes(unordered_set<int> &ids);
    void narrow_set_KC(unordered_set<int> &ids);
    void choice_pipe(unordered_set<int> &ids);
    void choice_KC(unordered_set<int> &ids);
    void delete_connection(int& v);
    set<int> find_connections(int &v);
    void dfs(int& v, vector<char>& cl, vector<int>& p, int& cycleStart, vector<int>& result);

public:

    unordered_map<int, vector<int>> ribs;
    unordered_map<int, Pipe> pipes;
    unordered_map<int, KC> KCs;
    void topologicalSort();
    void FullClearGraph();
    void ClearGraph();
    void CreateGraph();
    void del();
    void add_pipe();
    void add_KC();
    void display_objects();
    void change_pipe();
    void change_KC();
    void save_data();
    void download_data();
    void addConnection();
    void removeConnection();
    void displayConnections();
    void DisplayGraph();
    void sortConnections();
};

template <typename T, typename U>
using Filter = bool (*)(const T &t, U param);

template <typename T>
inline bool filter_name(const T &obj, string name)
{
    return name == obj.Name.substr(0, name.size());
}

inline bool filter_status(const Pipe &p, bool status)
{
    return (p.Status == status) ? (1) : (0);
}

inline bool filter_diameter(const Pipe &p, int diameter)
{
    return diameter == p.Diameter;
}

inline bool filter_amount_more(const KC &k, double amount_of)
{
    return (((double)k.Amount - (double)k.Working_amount) / (double)k.Amount >= (amount_of / 100.0)) ? (1) : (0);
}

inline bool filter_amount_less(const KC &k, double amount_of)
{
    return (((double)k.Amount - (double)k.Working_amount) / (double)k.Amount <= (amount_of / 100.0)) ? (1) : (0);
}

template <typename T, typename U>
inline void usefilter(unordered_set<int> &ids, unordered_map<int, T> obj, Filter<T, U> f, U param)
{
    for (int id : ids)
    {
        if (!f(obj[id], param))
        {
            ids.erase(id);
        }
    }
}



inline unordered_set<int> choose_id(unordered_set<int> mas)
{
    unordered_set<int> Ids;
    cout << "Choose id (choose -1 if you are done)" << endl;
    while (1)
    {
        int ID;
        ID = input_value<int>(-1, 9999);
        if (ID == -1)
            break;
        if (search(ID, mas))
        { // data type maS
            Ids.insert(ID);
        }
        else
        {
            printpar(cout, mas);
        }
        if (Ids.size() == mas.size())
        {
            cout << "All IDs are choosed" << endl;
            break;
        }
    }
    return Ids;
}

template <typename T>
inline unordered_set<int> read_ids(const unordered_map<int, T> container)
{
    unordered_set<int> ids;
    for (auto &pair : container)
    {
        ids.insert(pair.first);
    }
    return ids;
}

template <typename T>
inline void display(unordered_map<int, T> &mas, const unordered_set<int> &ids)
{
    for (int i : ids)
    {
        cout << mas[i] << endl;
    }
}







template <typename T>
inline void save_object(unordered_map<int, T> &container, ofstream &out)
{
    out << container.size() << endl;
    if (!container.empty())
    {
        for (const auto &pair : container)
        {
            T obj = pair.second;
            obj.save(out);
        }
    }
}

template <typename T>
inline void download_object(unordered_map<int, T> &container, ifstream &in)
{
    container.clear();
    int i;
    in >> i;
    for (int j = 0; j < i; j++)
    {
        in >> ws;
        T obj;
        obj.download(in);
        container.insert({obj.getId(), obj});
    }
    in >> ws;
}
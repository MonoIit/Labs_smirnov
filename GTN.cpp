#include "GTN.h"

using namespace std;


void GTN::add_pipe()
{
    Pipe pipe;
    pipe.create();
    pipes.insert({pipe.getId(), pipe});
}

void GTN::add_KC()
{
    KC KC;
    KC.create();
    int kc_id = KC.getId();
    KCs.insert({kc_id, KC});
}

void GTN::display_objects()
{
    cout << "1. Display pipes" << endl;
    cout << "2. Display KCs" << endl;
    cout << "3. Display all" << endl;
    unordered_set<int> IDS_p;
    unordered_set<int> IDS_k;
    IDS_p = read_ids(pipes);
    IDS_k = read_ids(KCs);
    switch (input_value<int>(1, 3))
    {
    case 3:
    {
        if (!pipes.empty())
        {
            display(pipes, IDS_p);
        }
        else
        {
            printpar(cout, pipes)
        }
        if (!KCs.empty())
        {
            display(KCs, IDS_k);
        }
        else
        {
            printpar(cout, KCs)
        }
        break;
    }
    case 1:
    {
        if (!pipes.empty())
        {
            narrow_set_pipes(IDS_p);
        }
        else
        {
            printpar(cout, pipes)
        }
        break;
    }
    case 2:
    {
        if (!KCs.empty())
        {
            narrow_set_KC(IDS_k);
        }
        else
        {
            printpar(cout, KCs)
        }
        break;
    }
    }
}

void GTN::change_pipe()
{
    if (!pipes.empty())
    {
        cout << "1. Use filter" << endl;
        cout << "2. Do not use filter" << endl;
        unordered_set<int> IDS;
        IDS = read_ids(pipes);
        switch (input_value<int>(1, 2))
        {
        case 1:
        {
            narrow_set_pipes(IDS);
            break;
        }
        case 2:
        {
            display(pipes, IDS);
            break;
        }
        }
        choice_pipe(IDS);
        ClearGraph();
        CreateGraph();
    }
    else
    {
        printpar(cout, pipes)
    }
}

void GTN::change_KC()
{
    if (!KCs.empty())
    {
        cout << "1. Use filter" << endl;
        cout << "2. Do not use filter" << endl;
        unordered_set<int> IDS;
        IDS = read_ids(KCs);
        switch (input_value<int>(1, 2))
        {
        case 1:
        {
            narrow_set_KC(IDS);
            break;
        }
        case 2:
        {
            display(KCs, IDS);
            break;
        }
        }
        choice_KC(IDS);
        ClearGraph();
        CreateGraph();
    }
    else
    {
        printpar(cout, KCs)
    }
}

void GTN::save_data()
{
    cout << "Enter path to save( /path/file_name)" << endl;
    ofstream out;
    out.open(read_string());
    if (out.is_open())
    {
        save_object(pipes, out);
        save_object(KCs, out);
    }
    out.close();
}

void GTN::download_data()
{
    cout << "Enter file name to download from" << endl;
    ifstream fin;
    fin.open(read_string());
    if (fin.is_open())
    {
        download_object(pipes, fin);
        download_object(KCs, fin);
    }
    fin.close();
}

void GTN::addConnection()
{
    ClearGraph();
    if (KCs.size() >= 2)
    {
        vector<int> result;
        cout << "Enter diameter" << endl;
        int diameter;
        diameter = input_diameter();
        for (auto&[pId, p] : pipes)
        {
            if (p.Diameter == diameter && !p.linked())
            {
                result.push_back(pId);
            }
        }
        int pipeId;
        if (result.empty())
        {
            Pipe obj;
            obj.create(diameter);
            pipes.insert({obj.getId(), obj});
            pipeId = obj.getId();
        }
        else
            pipeId = result[0];

        cout << "Enter KC id out" << endl;
        int KCfromId;
        KCfromId = input_value<int>();
        KCfromId = search(KCfromId, KCs);
        cout << "Enter KC id in" << endl;
        int KCtoId;
        KCtoId = input_value<int>();
        KCtoId = search(KCtoId, KCs);
        if (pipes[pipeId].connect_from == pipes[pipeId].connect_to && KCfromId != KCtoId && KCfromId != -1 && KCtoId != -1)
        {   
            pipes[pipeId].createLink(KCfromId, KCtoId);
            KCs[KCfromId].createlink();
            KCs[KCtoId].createlink();
        }
        else {
            cout << "error" << endl;
        }
    }
    else
    {
        cout << "Not enough pipes or KC" << endl;
    }
    CreateGraph();
}

void GTN::FullClearGraph()
{
    for (auto&[pipeId, pipe] : pipes)
    {
        if (pipe.linked())
        {
            KCs[pipe.connect_from].removelink();
            KCs[pipe.connect_to].removelink();
            pipe.removeLink();
        }
    }
    ClearGraph();
}

void GTN::removeConnection()
{
    ClearGraph();
    if (pipes.size() > 0 && KCs.size() > 1)
    {
        cout << "Enter pipe id to disconnect" << endl;
        int pipeId;
        pipeId = input_value<int>();
        int pipeIdError = pipeId;
        pipeId = search(pipeId, pipes);
        if (pipeId != -1 && pipes[pipeId].linked())
        {
            KCs[pipes[pipeId].connect_from].removelink();
            KCs[pipes[pipeId].connect_to].removelink();
            pipes[pipeId].removeLink();
        }
        else
            cout << "Pipe this id " << pipeIdError << " not found" << endl;
    }
    else
        cout << "There no pipes or KCs" << endl;
    CreateGraph();
}

void GTN::displayConnections()
{
    int flag = 0;
    if (pipes.size() > 0 && KCs.size() > 1)
    {
        for (auto&[id, pipe] : pipes)
        {
            if (pipe.linked())
                pipe.showLink();
                flag++;
        }
        if (!flag)
            cout << "There are no connected pipes" << endl;
    }
    else
        cout << "There no pipes or KCs" << endl;
}

set<int> GTN::CreateIndexes(const unordered_map<int, Pipe> &pipes, const unordered_map<int, KC> &KCs)
{
    set<int> peaks;
    for (auto&[id, pipe] : pipes)
    {
        if (KCs.count(pipe.connect_from) && KCs.count(pipe.connect_to))
        {
            peaks.insert(pipe.connect_from);
            peaks.insert(pipe.connect_to);
        }
    }
    return peaks;
}

void GTN::CreateGraph()
{
    set<int> indexes = CreateIndexes(pipes, KCs);
    if (!indexes.empty())
    {
        for (int v : indexes)
        {
            vector<int> peaks;
            ribs.insert({v, peaks});
        }
        for (auto&[id, pipe] : pipes)
        {
            if (pipe.connect_from != -1 && pipe.connect_from != -1 && pipe.connect_from != pipe.connect_to)
                ribs[pipe.connect_from].push_back(pipe.connect_to);
        }
        this->created = true;
    }
}

void GTN::DisplayGraph()
{
    if (created)
    {
        for (auto&[v, peaks] : ribs)
        {
            cout << v << " --> ";
            for (int j = 0; j < peaks.size(); j++)
                cout << peaks[j] << " ";
            cout << endl;
        }
    }
    else
    {
        CreateGraph();
        for (auto &[v, peaks] : ribs)
        {
            cout << v << " --> ";
            for (int j = 0; j < peaks.size(); j++)
                cout << peaks[j] << " ";
            cout << endl;
        }
    }
}


/*void GTN::topologicalSortUtil(int v, bool visited[], stack<int> &Stack)
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
}*/

void GTN::action_pipes(unordered_set<int> &IDS)
{
    cout << "1. delete" << endl;
    cout << "2. change" << endl;
    switch (input_value<int>(1, 2))
    {
    case 1:
    {
        for (int id : IDS)
        {
            if (pipes[id].connect_from != -1 || pipes[id].connect_to != -1)
            {
                KCs[pipes[id].connect_from].removelink();
                KCs[pipes[id].connect_to].removelink();
                pipes[id].removeLink();
            }
            pipes.erase(id);
        }
        break;
    }
    case 2:
    {
        for (int id : IDS)
            pipes[id].change();
        break;
    }
    }
}

void GTN::action_KCs(unordered_set<int> &IDS)
{
    cout << "1. delete" << endl;
    cout << "2. change" << endl;
    switch (input_value<int>(1, 2))
    {
    case 1:
    {
        for (int id : IDS)
        {
            if (KCs[id].linked())
                delete_connection(id);
            KCs.erase(id);
        }
        break;
    }
    case 2:
    {
        for (int id : IDS)
            KCs[id].change();
        break;
    }
    }
}

void GTN::narrow_set_pipes(unordered_set<int> &ids)
{
    bool flag = 1;

    do
    {
        cout << "1. Use filter by name" << endl;
        cout << "2. Use filter by status" << endl;
        cout << "3. Use filter by diameter" << endl;
        cout << "4. Stop using filter" << endl;

        switch (input_value<int>(1, 4))
        {
        case 1:
        {
            cout << "Enter the name" << endl;
            usefilter(ids, pipes, filter_name, read_string());
            break;
        }
        case 2:
        {
            cout << "Enter status(1/0)" << endl;
            usefilter(ids, pipes, filter_status, input_value<bool>(0, 1));
            break;
        }
        case 3:
        {
            cout << "Enter the diameter" << endl;
            usefilter(ids, pipes, filter_diameter, input_diameter());
            break;
        }
        case 4:
        {
            flag = 0;
            break;
        }
        }
        display(pipes, ids);
    } while (flag && !ids.empty());
}

void GTN::narrow_set_KC(unordered_set<int> &ids)
{
    bool flag = 1;

    do
    {
        cout << "1. Use filter by name" << endl;
        cout << "2. Use filter by amount(more)" << endl;
        cout << "3. Use filter by amount(less)" << endl;
        cout << "4. Stop using filter" << endl;

        switch (input_value<int>(1, 4))
        {
        case 1:
        {
            cout << "Enter the name" << endl;
            usefilter(ids, KCs, filter_name, read_string());
            break;
        }
        case 2:
        {
            cout << "Enter coef" << endl;
            usefilter(ids, KCs, filter_amount_more, input_value<double>(0, 100));
            break;
        }
        case 3:
        {
            cout << "Enter coef" << endl;
            usefilter(ids, KCs, filter_amount_less, input_value<double>(0, 100));
            break;
        }
        case 4:
        {
            flag = 0;
            break;
        }
        }
        display(KCs, ids);
    } while (flag && !ids.empty());
}

void GTN::choice_pipe(unordered_set<int> &ids)
{
    if (!ids.empty())
    {
        int per;
        cout << "1. chose handy" << endl;
        cout << "2. chose all" << endl;
        per = input_value<int>(1, 2);
        if (per == 1)
        {
            ids = choose_id(ids);
            action_pipes(ids);
        }
        else
        {
            action_pipes(ids);
        }
    }
}

void GTN::choice_KC(unordered_set<int> &ids)
{
    if (!ids.empty())
    {
        int per;
        cout << "1. chose handy" << endl;
        cout << "2. chose all" << endl;
        per = input_value<int>(1, 2);
        if (per == 1)
        {
            ids = choose_id(ids);
            action_KCs(ids);
        }
        else
        {
            action_KCs(ids);
        }
        
    }
}

set<int> GTN::find_connections(int &v)
{
    set<int> connections;
    for (auto &[id, pipe] : pipes)
        if (pipe.connect_from == v || pipe.connect_to == v)
            connections.insert(id);
    return connections;
}

void GTN::ClearGraph()
{
    ribs.clear();
    this->created = false;
}

void GTN::del()
{
    ribs[2].clear();
}

void GTN::delete_connection(int &v)
{
    set<int> connections = find_connections(v);
    for (int i : connections)
    {
        KCs[pipes[i].connect_from].removelink();
        KCs[pipes[i].connect_to].removelink();
        pipes[i].removeLink();
    }
}

void GTN::dfs(int &v, vector<char> &cl, vector<int> &p, int &cycleStart, vector<int> &result)
{
    cl[v] = 1;
    for (int i = 0; i < ribs[v].size(); i++)
    {
        int to = ribs[v][i];
        if (cl[to] == 0)
        {
            p[to] = v;
            dfs(to, cl, p, cycleStart, result);
        }
        else if (cl[to] == 1)
        {
            cycleStart = to;
            return;
        }
    }
    result.push_back(v);
    cl[v] = 2;
}

void GTN::topologicalSort()
{
    int n = ribs.size();
    vector<int> result;
    vector<char> cl;
    vector<int> p;
    int cycleStart = -1;
    p.assign(n, -1);
    cl.assign(n, 0);
    result.clear();
    for (auto&[i, peaks] : ribs)
        if (cl[i] != 2)
        {
            int j = i;
            dfs(j, cl, p, cycleStart, result);
        }
    if (cycleStart == -1)
    {
        reverse(result.begin(), result.end());
        for (int i = 0; i < result.size(); i++)
            cout << result[i] << " ";
        cout << endl;
    }
    else
        cout << "There are cycle" << endl;
}
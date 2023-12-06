#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <format>
#include <chrono>
#include "pipe.h"
#include "KC.h"
#include "tools.h"
#include "GTN.h"

using namespace std;
using namespace chrono;

template <typename T>
void add_object(unordered_map<int, T> &container)
{
    T obj;
    obj.create();
    container.insert({obj.getId(), obj});
}

template <typename T>
void save_object(unordered_map<int, T> &container, ofstream &out)
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
void download_object(unordered_map<int, T> &container, ifstream &in)
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

template <typename T>
unordered_set<int> read_ids(const unordered_map<int, T> container)
{
    unordered_set<int> ids;
    for (auto &pair : container)
    {
        ids.insert(pair.first);
    }
    return ids;
}

unordered_set<int> choose_id(unordered_set<int> mas)
{
    unordered_set<int> Ids;
    cout << "Choose id (choose 0 if you are done)" << endl;
    while (1)
    {
        int ID;
        ID = input_value<int>(0, 9999);
        if (ID == 0)
            break;
        if (check_id(ID, mas))
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

void menu()
{
    cout << "1. Add pipeline" << endl;
    cout << "2. Add KC" << endl;
    cout << "3. Check elements" << endl;
    cout << "4. Change the pipeline" << endl;
    cout << "5. Change the KC" << endl;
    cout << "6. Save" << endl;
    cout << "7. Download" << endl;
    cout << "8. Connect KCs" << endl;
    cout << "0. Close" << endl;
}

template <typename T>
void display(unordered_map<int, T> &mas, const unordered_set<int> &ids)
{
    for (int i : ids)
    {
        cout << mas[i] << endl;
    }
}

void display_connections(const vector<vector<int>> &connections)
{
    for (vector<int> connect : connections)
    {
        for (int id : connect)
        {
            cout << id << " ";
        }
        cout << endl;
    }
}

template <typename T>
void action(unordered_map<int, T> &mas, const unordered_set<int> &IDS, vector<vector<int>>& connections)
{
    cout << "1. delete" << endl;
    cout << "2. change" << endl;
    switch (input_value<int>(1, 2))
    {
    case 1:
    {
        for (int id : IDS)
        {
            if (mas[id].connect == true)
            {
                vector<vector<int>>::iterator count = connections.begin();
                for (vector<int> pair : connections) 
                {
                    if (pair[0] == id || pair[1] == id || pair[2] == id)
                    {
                        
                        connections.erase(count);
                        display_connections(connections);
                    }
                    count++;
                }
                cout << "her" << endl;
            }
            cout << "end" << endl;
            mas.erase(id);
        }
        break;
    }
    case 2:
    {
        for (int id : IDS)
            mas[id].change();
        break;
    }
    }
}

template <typename T>
void choice(unordered_map<int, T> &mas, unordered_set<int> &ids, vector<vector<int>>& connections)
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
            action(mas, ids, connections);
        }
        else
        {
            action(mas, ids, connections);
        }
    }
}

void input_id(int& id, unordered_set<int>& ids)
{
    id = input_value<int>(0);
    while (1)
    {
        if (check_id(id, ids))
        {
            break;
        }
        else
        {
            cout << "No object with this id" << endl;
            id = input_value<int>(0);
        }
    }
}

void save_connections(const vector<vector<int>>& connections, ostream& out)
{
    out << connections.size() << endl;
    for (vector<int> pair : connections)
    {
        for (int id : pair)
        {
            out << id << endl;
        }
    }
}

void download_connections(vector<vector<int>> &connections, istream &in)
{
    connections.clear();
    vector<int> connect;
    int i;
    in >> i;
    for (int j = 0; j < i; j++)
    {
        connect.clear();
        for (int k = 0; k < 3; k++)
        {
            int id;
            in >> id;
            connect.push_back(id);
        }
        connections.push_back(connect);
    }
}

template <typename T, typename U>
using Filter = bool(*)(const T &t, U param);

template <typename T>
bool filter_name(const T &obj, string name)
{
    return name == obj.Name.substr(0, name.size());
}

bool filter_status(const Pipe &p, bool status)
{
    return (p.Status == status) ? (1) : (0);
}

bool filter_diameter(const Pipe& p, int diameter) {
    return diameter == p.Diameter;
}

bool filter_amount_more(const KC &k, double amount_of)
{
    return (((double)k.Amount - (double)k.Working_amount) / (double)k.Amount >= (amount_of / 100.0)) ? (1) : (0);
}

bool filter_amount_less(const KC &k, double amount_of)
{
    return (((double)k.Amount - (double)k.Working_amount) / (double)k.Amount <= (amount_of / 100.0)) ? (1) : (0);
}

template <typename T, typename U>
void usefilter(unordered_set<int> &ids, unordered_map<int, T> obj, Filter<T, U> f, U param)
{
    for (int id : ids)
    {
        if (!f(obj[id], param))
        {
            ids.erase(id);
        }
    }
}

void narrow_set_pipes(unordered_map<int, Pipe> &p, unordered_set<int> &ids)
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
            usefilter(ids, p, filter_name, read_string());
            break;
        }
        case 2:
        {
            cout << "Enter status(1/0)" << endl;
            usefilter(ids, p, filter_status, input_value<bool>(0, 1));
            break;
        }
        case 3: {
            cout << "Enter the diameter" << endl;
            usefilter(ids, p, filter_diameter, input_diameter());
            break;
        }
        case 4:
        {
            flag = 0;
            break;
        }
        }
        display(p, ids);
    } while (flag && !ids.empty());
}



void narrow_set_KC(unordered_map<int, KC> &k, unordered_set<int> &ids)
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
            usefilter(ids, k, filter_name, read_string());
            break;
        }
        case 2:
        {
            cout << "Enter coef" << endl;
            usefilter(ids, k, filter_amount_more, input_value<double>(0, 100));
            break;
        }
        case 3:
        {
            cout << "Enter coef" << endl;
            usefilter(ids, k, filter_amount_less, input_value<double>(0, 100));
            break;
        }
        case 4:
        {
            flag = 0;
            break;
        }
        }
        display(k, ids);
    } while (flag && !ids.empty());
}

void chose_KC(unordered_map<int, KC>& KCs, unordered_set<int>& ids_k,  vector<int>& connect)
{
    display(KCs, ids_k);
    cout << "Enter enter KC`s id" << endl;
    int id;
    input_id(id, ids_k);
    KCs[id].connect_status = true;
    connect.push_back(id);
    ids_k.erase(id);
}

void chose_pipe(unordered_map<int, Pipe>& pipes, unordered_set<int>& ids, vector<int>& connect)
{
    cout << "Enter pipe diameter" << endl;
    int id;
    int diameter;
    diameter = input_diameter();
    usefilter(ids, pipes, filter_diameter, diameter);
    if (!ids.empty())
    {
        display(pipes, ids);
        cout << "Enter pipe id" << endl;
        input_id(id, ids);
    }
    else
    {
        add_object(pipes);
        ids = read_ids(pipes);
        usefilter(ids, pipes, filter_diameter, diameter);
        for (int idg : ids)
        {
            id = idg;
        }
    }
    pipes[id].connect_status = true;
    connect.push_back(id);
}

void check_connection(const vector<int>& connect, vector<vector<int>>& connections) {
    for (vector<int> pairs : connections)
    {
        if (pairs == connect)
        {
            cout << "This connect is already exists" << endl;
            return;
        }
    }
    connections.push_back(connect);
}

void remove_used_pipes(unordered_set<int> &ids_p, const vector<vector<int>> &connections)
{
    for (vector<int> pair : connections)
    {
        if (check_id(pair[1], ids_p))
        {
            ids_p.erase(pair[1]);
        }
    }
}

int main()
{
    redirect_output_wrapper cerr_out(cerr);
    string time = "now";
    // string time = std::format("{:%d_%m_%Y %H_%M_%OS}", system_clock::now());
    ofstream logfile("log_" + time);
    if (logfile)
        cerr_out.redirect(logfile);
    vector<vector<int>> connections;
    unordered_map<int, Pipe> pipes;
    unordered_map<int, KC> KCs;
    GTN GTN(KCs.size());
    bool flag = true;
    while (flag)
    {
        menu();
        switch (input_value<int>(0, 8))
        {
        case 1:
        {
            add_object(pipes);
            break;
        }
        case 2:
        {
            add_object(KCs);
            break;
        }
        case 3:
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
                    narrow_set_pipes(pipes, IDS_p);
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
                    narrow_set_KC(KCs, IDS_k);
                }
                else
                {
                    printpar(cout, KCs)
                }
                break;
            }
            }
            break;
        }
        case 4:
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
                    narrow_set_pipes(pipes, IDS);
                    break;
                }
                case 2:
                {
                    display(pipes, IDS);
                    break;
                }
                }
                choice(pipes, IDS, connections);
            }
            else
            {
                printpar(cout, pipes)
            }
            break;
        }
        case 5:
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
                    narrow_set_KC(KCs, IDS);
                    break;
                }
                case 2:
                {
                    display(KCs, IDS);
                    break;
                }
                }
                choice(KCs, IDS, connections);
            }
            else
            {
                printpar(cout, KCs)
            }
            break;
        }
        case 6:
        {
            cout << "Enter path to save( /path/file_name)" << endl;
            ofstream out;
            out.open(read_string());
            if (out.is_open())
            {
                save_object(pipes, out);
                save_object(KCs, out);
                save_connections(connections, out);
            }
            out.close();
            break;
        }
        case 7:
        {
            cout << "Enter file name to download from" << endl;
            ifstream fin;
            fin.open(read_string());
            if (fin.is_open())
            {
                download_object(pipes, fin);
                download_object(KCs, fin);
                download_connections(connections, fin);
            }
            fin.close();
            break;
        }
        case 8:
        {
            vector<int> connect;
            unordered_set<int> ids_p;
            unordered_set<int> ids_k;
            ids_p = read_ids(pipes);
            display_connections(connections);
            remove_used_pipes(ids_p, connections);
            ids_k = read_ids(KCs);
            chose_KC(KCs, ids_k, connect);
            chose_pipe(pipes, ids_p, connect);
            chose_KC(KCs, ids_k, connect);
            
            break;
        }
        case 0:
        {
            flag = false;
            break;
        }
        default:
        {
            cout << "please, enter suggested numbers" << endl;
            break;
        }
        }
    }
    cerr << 0;
    return 0;
}

// Логирование

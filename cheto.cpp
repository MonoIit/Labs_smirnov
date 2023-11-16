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
void save_object(unordered_map<int, T> &container, ofstream &out, const string &fname)
{
    out.open(fname, ios_base::app);
    out << container.size() << endl;
    if (!container.empty())
    {
        for (const auto &pair : container)
        {
            T obj = pair.second;
            obj.save(out);
        }
    }
    out.close();
}

template <typename T>
void download_object(unordered_map<int, T> &container, ifstream &in)
{
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

bool check_id(const int &r, unordered_set<int> &mas)
{
    return mas.count(r) > 0;
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
    cout << "5. Change the ceh" << endl;
    cout << "6. Save" << endl;
    cout << "7. Download" << endl;
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

template <typename T>
void action(unordered_map<int, T> &mas, const unordered_set<int> &IDS)
{
    cout << "1. delete" << endl;
    cout << "2. change" << endl;
    switch (input_value<int>(1, 2))
    {
    case 1:
    {
        for (int j : IDS)
        {
            mas.erase(j);
        }
        break;
    }
    case 2:
    {
        for (int j : IDS)
        {
            mas[j].change();
        }
        break;
    }
    }
}

template <typename T>
void choice(unordered_map<int, T> &mas, unordered_set<int> &ids)
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
            action(mas, ids);
        }
        else
        {
            action(mas, ids);
        }
    }
}

template <typename T, typename U>
using Filter = bool (*)(const T &t, U param);

template <typename T>
bool filter_name(const T &obj, string name)
{
    return name == obj.Name.substr(0, name.size());
}

bool filter_status(const Pipe &p, bool status)
{
    return (p.Status == status) ? (1) : (0);
}

bool filter_amount_more(const KC &k, double amount_of)
{
    return ((double)k.Working_amount / (double)k.Amount >= (amount_of / 100.0)) ? (1) : (0);
}

bool filter_amount_less(const KC &k, double amount_of)
{
    return ((double)k.Working_amount / (double)k.Amount <= (amount_of / 100.0)) ? (1) : (0);
}

template <typename T, typename U>
void usefilter(unordered_set<int> &ids, unordered_map<int, T> obj, Filter<T, U> f, U param)
{
    for (int i : ids)
    {
        if (!f(obj[i], param))
        {
            ids.erase(i);
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
        cout << "3. Stop using filter" << endl;

        switch (input_value<int>(1, 3))
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
        case 3:
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

int main()
{
    redirect_output_wrapper cerr_out(cerr);
    string time = "now";
    // string time = std::format("{:%d_%m_%Y %H_%M_%OS}", system_clock::now());
    ofstream logfile("log_" + time);
    if (logfile)
        cerr_out.redirect(logfile);
    unordered_map<int, Pipe> pipes;
    unordered_map<int, KC> KCs;
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
                else {
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
                choice(pipes, IDS);
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
                choice(KCs, IDS);
            }
            else
            {
                printpar(cout, KCs)
            }
            break;
        }
        case 6:
        {
            cout << "Enter file name to save" << endl;
            ofstream out;
            string fname;
            fname = read_string();
            out.open(fname);
            out.close();
            save_object(pipes, out, fname);
            save_object(KCs, out, fname);
            break;
        }
        case 7:
        {
            pipes.clear();
            KCs.clear();
            cout << "Enter file name download from" << endl;
            ifstream in(read_string());
            download_object(pipes, in);
            download_object(KCs, in);
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
    return 0;
}

// Логирование

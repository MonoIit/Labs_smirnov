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
vector<int> choose_id(const unordered_map<int, T>& mas) {
    #define printwar(out, mas) out << "No " << #mas << " with this ID" << endl;
    unordered_set<int> Ids;
    cout << "Choose id (choose 0 if you are done)" << endl;
    while(1) {
        int ID;
        ID = input_value<int>(0, 9999);
        if (ID == 0) 
            break;
        if (check_id(ID, mas)) {
            Ids.insert(ID);
        } else {
            printwar(cout, mas);
        }
        if (Ids.size() == mas.size()) {
            cout << "All IDs are choosed" << endl;
            break;
        }
    }
    return vector<int>(Ids.begin(), Ids.end());
}







void menu() {
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
void view(const unordered_map<int, T>& mas) {
    for (const auto& p: mas) {
        cout << p.second;
    }
}

template <typename T>
bool check_id(const int& r, const unordered_map<int, T>& mas) {
    return mas.count(r)>0;
}




template <typename T>
void viewAll(const unordered_map<int, T>& mas) {
    if (!mas.empty()) {
            view(mas);
        } else {
            printpar(cout, mas);
        }
}

template <typename T, typename U>
using Filter = bool(*)(const T& t, U param);

template <typename T>
bool filter_name(const T& t, string name) {
    return name == t.Name.substr(0, name.size());
}

bool filter_status(const Pipe& p, bool status){
    return (p.Status == status) ? (1) : (0);
}

bool filter_amount_more(const KC& k, double amount_of) {
    return ((double)k.Working_amount/(double)k.Amount >= (amount_of/100.0)) ? (1) : (0);
}

bool filter_amount_less(const KC& k, double amount_of) {
    return ((double)k.Working_amount/(double)k.Amount <= (amount_of/100.0)) ? (1) : (0);
}

template <typename T, typename U>
vector<int> usefilter(const unordered_map<int, T>& mas, Filter<T, U> f, U param) {
    vector <int> res;
	for (auto& s : mas) {
		if (f(s.second, param))
			res.push_back(s.first);
	}
	return res;
}

void useFilterP(unordered_map<int, Pipe>& mas) {
    cout << "1. Use filter by name" << endl;
    cout << "2. Use filter by status" << endl;
    int fltr;
    fltr = input_value<int>(1, 2);
    if (fltr == 1) {
        string name;
        cout << "Enter the name" << endl;
        name = read_string();
        for (int i : usefilter(mas, filter_name, name)) {
            cout << mas[i];
        }
    } else if (fltr == 2) {
        bool value;
        cout << "Enter status(1/0)" << endl;
        cin >> value;
        for (int i : usefilter(mas, filter_status, value)) {
            cout << mas[i];
        }
    }
}

void useFilterK(unordered_map<int, KC>& mas) {
    cout << "1. Use filter by name" << endl;
    cout << "2. Use filter by amount(more)" << endl;
    cout << "3. Use filter by amount(less)" << endl;
    int fltr;
    fltr = input_value<int>(1, 3);
    if (fltr == 1) {
        string name;
        cout << "Enter the name" << endl;
        name = read_string();
        for (int i : usefilter(mas, filter_name, name)) {
            cout << mas[i];
        }
    } else if (fltr == 2) {
        double value;
        cout << "Enter coef" << endl;
        value = input_value<double>(0, 100);
        for (int i : usefilter(mas, filter_amount_more, value)) {
            cout << mas[i];
        }
    } else if (fltr == 3) {
        double value;
        cout << "Enter coef" << endl;
        value = input_value<double>(0, 100);
        for (int i : usefilter(mas, filter_amount_less, value)) {
            cout << mas[i];
        }
    }
}

int main() {
	redirect_output_wrapper cerr_out(cerr);
    string time = "now";
    //string time = std::format("{:%d_%m_%Y %H_%M_%OS}", system_clock::now());
	ofstream logfile("log_"+ time);
	if (logfile)
		cerr_out.redirect(logfile);
    unordered_map<int, Pipe> pipes;
    unordered_map<int, KC> KCs;
    bool flag1 = true;
    while (flag1) {
        menu();
        int n;
        n = input_value<int>(0, 8);
        switch (n)
        {
        case 1: {
            {
                Pipe pipe;
                pipe.add_pipe();
                pipes.insert({pipe.getId(), pipe});
            }
            break;
        }
        case 2: {
            {
                KC kc;
                kc.add_KC();
                KCs.insert({kc.getId(), kc});
            }
            break;
        }
        case 3: {
            cout << "1. Display pipes" << endl;
            cout << "2. Display KCs" << endl;
            cout << "3. Display all" << endl;
            int choice1;
            choice1 = input_value<int>(1, 3);
            while(1) {
                if (choice1 == 3) {
                    viewAll(pipes);
                    viewAll(KCs);
                    break;
                } else if (choice1 == 1) {
                    useFilterP(pipes);
                    break;
                } else if (choice1 == 2) {
                    useFilterK(KCs);
                    break;
                } else {
                    cout << "try again" << endl;
                }
            }
            break;
        }
        case 4: {
            if (!pipes.empty()) {
                cout << "1. Delete" << endl;
                cout << "2. Change status" << endl;
                int i;
                vector<int> Ids;
                while(1) {
                    i = input_value<int>(1, 2);
                    if (i == 2) {
                        useFilterP(pipes);
                        Ids = choose_id(pipes);
                        if (!Ids.empty()) {
                            for (int j : Ids) {
                                pipes[j].change_pipe();
                            }
                        } else {
                            cout << "You did not choose id" << endl;
                        }
                        break;
                    } else if (i == 1) {
                        useFilterP(pipes);
                        Ids = choose_id(pipes);
                        if (!Ids.empty()) {
                            for (int j : Ids) {
                                pipes.erase(j);
                            }
                        } else {
                            cout << "You did not choose id" << endl;
                        }
                        break;
                    } else {
                        cout << "try again" << endl;
                    }
                }      
            } else {
                printpar(cout, pipes);
            }
            break;
        }
        case 5: {
            if (!KCs.empty()) {
                cout << "1. Delete" << endl;
                cout << "2. Change amount of working" << endl;
                int i;
                vector<int> Ids;
                while(1) {
                    i = input_value<int>(1, 2);;
                    if (i == 2) {
                        useFilterK(KCs);
                        Ids = choose_id(KCs);
                        if (!Ids.empty()) {
                            for (int j : Ids) {
                                KCs[j].change_KC();
                            }
                        } else {
                            cout << "You did not choose id" << endl;
                        }
                        break;
                    } else if (i == 1) {
                        useFilterK(KCs);
                        Ids = choose_id(KCs);
                        if (!Ids.empty()) {
                            for (int j : Ids) {
                                KCs.erase(j);
                            }
                        } else {
                            cout << "You did not choose id" << endl;
                        }
                        break;
                    } else {
                        cout << "try again" << endl;
                    }
                }      
            } else {
                printpar(cout, KCs);
            }
            break;
        }
        case 6: {
            cout << "Enter file name to save" << endl;
            string fname;
            fname = read_string();
            ofstream out;
            out.open(fname);
            out.close();
            if (!pipes.empty()) {
                out.open(fname, ios_base::app);
                out << "pipes" << endl;
                out << pipes.size() << endl;
                for (const auto& p: pipes) {
                    Pipe P = p.second;
                    P.save_pipe(out);
                }
                out.close();
            }
            if (!KCs.empty()) {
                out.open(fname, ios_base::app);
                out << "KCs" << endl;
                out << KCs.size() << endl;
                for (const auto& k: KCs) {
                    KC K = k.second;
                    K.save_KC(out);
                }
                out.close();
            }
            break;
        }
        case 7: {
            pipes.clear();
            KCs.clear();
            cout << "Enter file name download from" << endl;
            string fname;
            fname = read_string();
            ifstream in(fname);
            string flag1;
            in >> flag1;
            if (flag1 != "KCs" & !flag1.empty()){
                int i;
                in >> i;
                for (int j = 0; j < i; j++) {
                    in >> ws;
                    Pipe p;
                    p.download_pipe(in);
                    pipes.insert({p.getId(), p});
                }
                in >> ws;
                in >> flag1;
            }
            in >> ws;
            if (!flag1.empty()) {
                int y;
                in >> y;
                for (int l = 0; l < y; l++) {
                    in >> ws;
                    KC k;
                    k.download_KC(in);
                    KCs.insert({k.getId(), k});
                }
            }
            in.close();
            if (!pipes.empty()) {
                for (const auto& p: pipes) {
                    cout << p.second;
                }
            } else {
                printpar(cout, pipes);
            }
            if (!KCs.empty()) {
                for (const auto& k: KCs) {
                    cout << k.second;
                }
            } else {
                printpar(cout, KCs);
            }
            break;
        }
        case 0: {
            flag1 = false;
            break;  
        }  
        default: {
            cout << "please, enter suggested numbers" << endl;
            break;
        }
        }
    }
    return 0;
}

// Логирование










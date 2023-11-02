#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <format>
#include <chrono>
#include "pipe.h"
#include "KC.h"
#include "tools.h"

using namespace std;
using namespace chrono;

template <typename T>
vector<int> choose_id(const unordered_map<int, T>& mas) {
    vector<int> Ids;
    cout << "Choose pipe`s id (choose 0 if you are done)" << endl;
    cerr << "User choosing IDs" << endl;
    while(1) {
        int ID;
        ID = check_int();
        if (ID == 0) {
            cerr << "User stoped choosing IDs" << endl;
            break;
        } else if (find(Ids.begin(), Ids.end(), ID) != Ids.end()) {
            cout << "This ID has already choosen" << endl;
            cerr << "User chose ID that is already chosen";
        } else if (check_id(ID, mas)) {
            Ids.push_back(ID);
            cerr << "User chose ID: " << ID << endl;
        } else {
            cout << "No pipe with this ID" << endl;
            cerr << "User choose incorrect ID" << endl;
        }
        if (Ids.size() == mas.size()) {
            cerr << "All IDs are choosed" << endl;
            break;
        }
    }
    cerr << "IDs have been choosen" << endl;
    return Ids;
}

template <typename T>
void filter_name(const unordered_map<int, T>& mas) {
    string find;
    cout << "Enter name" << endl;
    find = read_string();
    cerr << "User chose name for using filter" << endl;
    for (const auto& m : mas) {
        if (m.second.Name.find(find) != string::npos) {
            cout << m.second;
        }
    }
    cerr << "Objects has been displayed" << endl;
}

void filterP(const unordered_map<int, Pipe>& pipes) {
    cerr << "User used filter for pipes" << endl;
    cout << "1. find by name" << endl;
    cout << "2. find by status" << endl;
    while(1) {
        int i;
        i = check_int();
        if (i == 1) {
            cerr << "User used filter by names" << endl;
            filter_name(pipes);
        } else if (i == 2) {
            cerr << "User used filter by status" << endl;
            cout << "1. find working pipes" << endl;
            cout << "2. find repairing pipes" << endl;
            while(1) {
                int j;
                j = check_int();
                if (j == 1) {
                    cerr << "User found working pipes" << endl;
                    for (const auto& p : pipes) {
                        if (p.second.Status == 1) {
                            cout << p.second;
                            cerr << "Pipe with ID: " << p.second.getId() << "has been displayed" << endl;
                        }
                    }
                } else if (j == 2) {
                    cerr << "User found repairing pipes" << endl;
                    for (const auto& p : pipes) {
                        if (p.second.Status == 0) {
                            cout << p.second;
                            cerr << "Pipe with ID: " << p.second.getId() << "has been displayed" << endl;
                        }
                    }
                } else {
                    cout << "try again" << endl;
                    cerr << "User chose incorrect option" << endl;
                }
                cerr << "Pipes have been displayed" << endl;
                break;
            }
            break;
        } else {
            cout << "try again" << endl;
            cerr << "User chose incorrect option" << endl;
        }
        cerr << "User stoped using filter" << endl;
        break;
    }
}


///log
void filterK(const unordered_map<int, KC>& KCs) {
    cerr << "User used filter for KCs" << endl;
    cout << "1. find by name" << endl;
    cout << "2. find by unused cehs" << endl;
    while(1) {
        int i;
        i = check_int();
        if (i == 1) {
            cerr << "User used filter by names" << endl;
            filter_name(KCs);
        } else if (i == 2) {
            cerr << "User chose filter by unused cehs" << endl;
            cout << "1. Less than..." << endl;
            cout << "2. More than..." << endl;
            while(1) {
                int j;
                j = check_int();
                if (j == 1) {
                    double h = check_double();
                    for (const auto& k : KCs) {
                        if (k.second.Working_amount/k.second.Amount <= h) {
                            cout << k.second;
                            cerr << "KC with ID: " << k.second.getId() << "has been displayed" << endl;
                        }
                    }
                } else if (j == 2) {
                    double h = check_double();
                    for (const auto& k : KCs) {
                        if (k.second.Working_amount/k.second.Amount >= h) {
                            cout << k.second;
                            cerr << "KC with ID: " << k.second.getId() << "has been displayed" << endl;
                        }
                    }
                } else {
                    cout << "try again" << endl;
                    cerr << "User chose incorrect option" << endl;
                }
                break;
            }
            break;
        } else {
            cout << "try again" << endl;
            cerr << "User chose incorrect option" << endl;
        }
        cerr << "User stoped using filter" << endl;
        break;
    }
}


void menu() {
    cout << "1. Add pipeline" << endl;
    cout << "2. Add KC" << endl;
    cout << "3. Check all elements" << endl;
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
    for (const auto& m: mas) {
        if (m.first == r) {
            return true;
        }
    }
    return false;
}


int main() {
	redirect_output_wrapper cerr_out(cerr);
	string time = "new";
	ofstream logfile("log_"+ time);
	if (logfile)
		cerr_out.redirect(logfile);
    cerr << "Programm start" << endl;
    unordered_map<int, Pipe> pipes;
    unordered_map<int, KC> KCs;
    bool flag1 = true;
    while (flag1) {
        menu();
        int n;
        n = check_int();
        cerr << "User chose option " << n << endl; 
        switch (n)
        {
        case 1: {
            {
                Pipe pipe;
                pipe.add_pipe();
                pipes.insert({pipe.getId(), pipe});
                cerr << "User added a pipe" << endl;
            }
            break;
        }
        case 2: {
            {
                KC kc;
                kc.add_KC();
                KCs.insert({kc.getId(), kc});
                cerr << "User added a KC" << endl;
            }
            break;
        }
        case 3: {
            if (!pipes.empty()) {
                view(pipes);
            } else {
                cout << "no pipelines\n";
            }
            if (!KCs.empty()) {
                view(KCs);
            } else {
                cout << "no KCs\n";
            }
            break;
        }
        case 4: {
            if (!pipes.empty()) {
                cout << "1. Delete" << endl;
                cout << "2. Change status" << endl;
                int i;
                bool fltr;
                vector<int> Ids;
                while(1) {
                    i = check_int();
                    if (i == 2) {
                        cout << "Use filter(Y/n)" << endl;
                        fltr = check_bool();
                        if (fltr) {
                            filterP(pipes);
                        } else {
                            view(pipes);
                        }
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
                        cout << "Use filter(Y/n)" << endl;
                        fltr = check_bool();
                        if (fltr) {
                            filterP(pipes);
                        } else {
                            view(pipes);
                        }
                        Ids = choose_id(pipes);
                        if (!Ids.empty()) {
                            for (int j : Ids) {
                                pipes.erase(j);
                                cerr << "User deleted a pipe with id " << j << endl; 
                            }
                        } else {
                            cout << "You did not choose id" << endl;
                            cerr << "User did not choose id" << endl;
                        }
                        break;
                    } else {
                        cout << "try again" << endl;
                        cerr << "User choose incorrect option" << endl;
                    }
                }      
            } else {
                cout << "No pipelines" << endl;
            }
            break;
        }
        case 5: {
            if (!KCs.empty()) {
                cout << "1. Delete" << endl;
                cout << "2. Change amount of working" << endl;
                int i;
                bool fltr;
                vector<int> Ids;
                while(1) {
                    i = check_int();
                    if (i == 2) {
                        cout << "Use filter(Y/n)" << endl;
                        fltr = check_bool();
                        if (fltr) {
                            filterK(KCs);
                        } else {
                            view(KCs);
                        }
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
                        cout << "Use filter(Y/n)" << endl;
                        fltr = check_bool();
                        if (fltr) {
                            filterK(KCs);
                        } else {
                            view(KCs);
                        }
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
                cout << "No pipelines" << endl;
            }
            break;
        }
        case 6: {
            cout << "Enter file name to save" << endl;
            string fname;
            fname = read_string();
            cerr << "User enter file name for saving" << endl;
            ofstream out;
            out.open(fname);
            out.close();
            if (!pipes.empty()) {
                out.open(fname, ios_base::app);
                out << "pipes" << endl;
                out << pipes.size() << endl;
                for (const auto& p: pipes) {
                    save_pipe(out, p.second);
                }
                out.close();
            }
            if (!KCs.empty()) {
                out.open(fname, ios_base::app);
                out << "KCs" << endl;
                out << KCs.size() << endl;
                for (const auto& k: KCs) {
                    save_KC(out, k.second);
                }
                out.close();
            }
            cerr << "User saved information in file " << fname << endl;
            break;
        }
        case 7: {
            cout << "Enter file name download from" << endl;
            string fname;
            fname = read_string();
            cerr << "User enter file name for download from" << endl;
            ifstream in(fname);
            string flag1;
            in >> flag1;
            if (flag1 != "KCs" & !flag1.empty()){
                int i;
                in >> i;
                for (int j = 0; j < i; j++) {
                    in >> ws;
                    Pipe p;
                    download_pipe(in, p);
                    pipes.insert({p.getId(), p});
                }
                in >> ws;
                in >> flag1;
            }
            in >> ws;
            if (!flag1.empty()) {
                int k;
                in >> k;
                for (int l = 0; l < k; l++) {
                    in >> ws;
                    KC k;
                    download_KC(in, k);
                    KCs.insert({k.getId(), k});
                }
            }
            in.close();
            if (!pipes.empty()) {
                for (const auto& p: pipes) {
                    cout << p.second;
                }
            } else {
                cout << "no pipelines\n";
            }
            if (!KCs.empty()) {
                for (const auto& k: KCs) {
                    cout << k.second;
                }
            } else {
                cout << "no KCs\n";
            }
            cerr << "User downloaded information" << endl;
            break;
        }
        case 0: {
            flag1 = false;
            cerr << "User finished work" << endl;
            break;  
        }  
        default: {
            cout << "please, enter suggested numbers" << endl;
            cerr << "User chose incorect option" << endl;
            break;
        }
        }
    }
    cerr << "Programm finished" << endl;
    return 0;
}

// Логирование










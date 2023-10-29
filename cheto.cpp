#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include "pipe.h"
#include "KC.h"
#include "tools.h"

using namespace std;


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

void viewPipes(const unordered_map<int, Pipe>& pipes) {
    for (const auto& p: pipes) {
        cout << p.second;
    }
}

void viewKCs(const unordered_map<int, KC>& KCs) {
    for (const auto& k: KCs) {
        cout << k.first << endl;
        cout << k.second;
    }
}

bool check_id(const int& r, const unordered_map<int, Pipe>& pipes) {
    for (const auto& p: pipes) {
        if (p.first == r) {
            return true;
        }
    }
    return false;
}

int main() {
    unordered_map<int, Pipe> pipes;
    unordered_map<int, KC> KCs;
    bool flag = true;
    while (flag) {
        menu();
        int n;
        n = check_int();
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
            if (!pipes.empty()) {
                viewPipes(pipes);
            } else {
                cout << "no pipelines\n";
            }
            if (!KCs.empty()) {
                viewKCs(KCs);
            } else {
                cout << "no KCs\n";
            }
            break;
        }
        case 4: {
            if (!pipes.empty()) {
                cout << "1. Change one pipe" << endl;
                cout << "2. Change some pipes" << endl;
                while (1) {
                    int choice;
                    cin >> choice;
                    if (choice == 1) {
                        viewPipes(pipes);
                        cout << "Choose pipe`s id" << endl;
                        while(1) {
                            int ID;
                            cin >> ID;
                            if (check_id(ID, pipes)) {
                                pipes[ID].change_pipe();
                                break;
                            } else {
                                cout << "No pipe with this ID" << endl;
                            }
                        }
                        break;
                    } else if (choice == 2) {
                        viewPipes(pipes);
                        vector<int> Ids;
                        cout << "Choose pipe`s id (choose 0 if you are done)" << endl;
                        while(1) {
                            int ID;
                            cin >> ID;
                            if (ID == 0) {
                                break;
                            } else if (find(Ids.begin(), Ids.end(), ID) != Ids.end()) {
                                cout << "This ID has already choosen" << endl;
                            } else if (check_id(ID, pipes)) {
                                Ids.push_back(ID);
                            } else {
                                cout << "No pipe with this ID" << endl;
                            }
                            if (Ids.size() == pipes.size()) {
                                break;
                            }
                        }
                        if (!Ids.empty()) {
                            for (int i : Ids) {
                                pipes[i].change_pipe();
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
        /*case 5: {
            if (!KC_1.Name.empty()) {
                KC_1.change_KC();
                cout << KC_1;
            } else {
                cout << "No KCs" << endl;
            }
            break;
        }*/
        case 6: {
            ofstream out;
            out.open("datas.txt");
            out.close();
            if (!pipes.empty()) {
                out.open("datas.txt", ios_base::app);
                out << "pipes" << endl;
                out << pipes.size() << endl;
                for (const auto& p: pipes) {
                    save_pipe(out, p.second);
                }
                out.close();
            }
            if (!KCs.empty()) {
                out.open("datas.txt", ios_base::app);
                out << "KCs" << endl;
                out << KCs.size() << endl;
                for (const auto& k: KCs) {
                    save_KC(out, k.second);
                }
                out.close();
            }
            break;
        }
        case 7: {
            ifstream in("datas.txt");
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

            break;
        }
        case 0: {
            flag = false;
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










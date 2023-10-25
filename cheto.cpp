#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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


int main() {
    Pipe pipeline_1;
    KC KC_1;
    bool flag = true;
    while (flag) {
        menu();
        int n;
        n = check_int();
        switch (n)
        {
        case 1: {
            pipeline_1.add_pipe();
            break;
        }
        case 2: {
            KC_1.add_KC();
            break;
        }
        case 3: {
            if (!pipeline_1.Name.empty()) {
                cout << pipeline_1;
            } else {
                cout << "no pipelines\n";
            }
            if (!KC_1.Name.empty()) {
                cout << KC_1;
            } else {
                cout << "no KCs\n";
            }
            break;
        }
        case 4: {
            if (!pipeline_1.Name.empty()) {
                pipeline_1.change_pipe();
                cout << pipeline_1;
            } else {
                cout << "No pipelines" << endl;
            }
            break;
        }
        case 5: {
            if (!KC_1.Name.empty()) {
                KC_1.change_KC();
                cout << KC_1;
            } else {
                cout << "No KCs" << endl;
            }
            break;
        }
        case 6: {
            ofstream out;
            out.open("datas.txt");
            out.close();
            if (!pipeline_1.Name.empty()) {
                out.open("datas.txt", ios_base::app);
                out << "pipes" << endl;
                save_pipe(out, pipeline_1);
                out.close();
            }
            if (!KC_1.Name.empty()) {
                out.open("datas.txt", ios_base::app);
                out << "KCs" << endl;
                save_KC(out, KC_1);
                out.close();
            }
            break;
        }
        case 7: {
            std::ifstream in("datas.txt");
            string flag1;
            in >> flag1;
            while (flag1 != "KCs" & !flag1.empty()) {
                download_pipe(in, pipeline_1);
                flag1 = "";
                in >> flag1;
            } 
            while (!flag1.empty()) {
                download_KC(in, KC_1);
                flag1 = "";
                in >> flag1;
            }
            in.close();
            if (!pipeline_1.Name.empty()) {
                cout << pipeline_1;
            } else {
                cout << "no pipelines\n";
            }
            if (!KC_1.Name.empty()) {
                cout << KC_1;
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










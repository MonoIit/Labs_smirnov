#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct pipeline 
{
    string Name;
    int Lenght;
    int Diameter;
    bool Status;
};

struct KC
{
    string Name;
    int Amount;
    int Working_amount;
    double Efficiency;
};



int check_int() {
    int value;
    cin >> value;
    while (cin.fail() || std::cin.peek() != '\n' || value < 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "try again" << endl;
        cin >> value;
    }
    return value;
}

string read_string() {
    string name;
    cin >> ws;
    getline(cin, name);
    return name;
}

double check_double() {
    double value;
    cin >> value;
    while (cin.fail() || std::cin.peek() != '\n' || value < 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "try again" << endl;
        cin >> value;
    }
    return value;
}

bool check_bool() {
    char value;
    cin >> value;
    while (1) 
    {
        if (value == 'n') {
            return 0;
        } else if (value == 'Y') {
            return 1;
        } else {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Enter Y/n" << endl;
            cin >> value;
        }
    }
}


void change_KC(KC& k)
 {
    cout << "Enter amount of working manufactories" << endl;
    while (1)
     {
        k.Working_amount = check_int();
        if (k.Working_amount <= k.Amount) 
            return;
        cout << "try again" << endl;
    }
 }
void get_KC_data(KC& k) {
    cout << "Enter manufactory name" << endl;
    k.Name = read_string();
    cout << "Enter amount of manufactories" << endl;
    k.Amount = check_int();
    cout << "Enter amount of working manufactories" << endl;
    bool flag = true;
    while (flag) {
        k.Working_amount = check_int();
        if (k.Working_amount <= k.Amount) {
            flag = false;
        } else {
            cout << "try again" << endl;
        }
    }
    cout << "Enter the value of 'efficiency'" << endl;
    k.Efficiency = check_double(); 
}

ostream& operator << (ostream& out, const KC& k) {
    out << "-----------------------" << endl;
    out << "Your KC:" << endl;
    out << "Name: " << k.Name << endl;
    out << "Amount of manufactories: " << k.Amount << endl;
    out << "Amount of working manufactories: " << k.Working_amount << endl;
    out << "The value of 'efficiency': " << k.Efficiency << endl;
    out << "-----------------------" << endl;
    return out;
}

KC add_KC() {
    KC k;
    get_KC_data(k);
    cout << k;
    return k;
}

void change_pipe(pipeline& p) {
    cout << "Is pipeline working? (Y/n)" << endl;
    p.Status = check_bool();
}


void get_pipe_data(pipeline& p) {
    cout << "Enter pipeline name" << endl;
    p.Name = read_string();
    cout << "Enter pipeline lenght" << endl;
    p.Lenght = check_int();
    cout << "Enter pipeline diameter" << endl;
    p.Diameter = check_int();
    cout << "Is pipeline working? (Y/n)" << endl;
    p.Status = check_bool();
}

ostream& operator << (ostream& out, const pipeline& p) {
    out << "-----------------------" << endl;
    out << "Your pipeline:" << endl;
    out << "Name: " << p.Name << endl;
    out << "Lenght: " << p.Lenght << endl;
    out << "Diameter: " << p.Diameter << endl;
    out << "Status: ";
    if (p.Status == 1) {
        out << "working" << endl;
    } else if (p.Status == 0) {
        out << "repairing" << endl;
    } else {
        out << "unknown" << endl;
    }
    out << "-----------------------" << endl;
    return out;
}

pipeline add_pipeline() {
    pipeline p;
    get_pipe_data(p);
    cout << p;
    return p;
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

void save_pipeline(ofstream& out, const pipeline& p) {
    out << p.Name << endl;
    out << p.Lenght << endl;
    out << p.Diameter << endl;
    out << p.Status << endl;
}

void save_KC(ofstream& out, const KC& k) {
    out << k.Name << endl;
    out << k.Amount << endl;
    out << k.Working_amount << endl;
    out << k.Efficiency << endl;
}

void download_pipeline(ifstream& in, pipeline& p) {
    {
        bool status;
        in >> ws;
        getline(in, p.Name);
        in >> p.Lenght >> p.Diameter >> status;
        p.Status = (status == 1) ? "working" : "repairing";
    }
}

void download_KC(ifstream& in, KC& k) {
    in >> ws;
    getline(in, k.Name);
    in >> k.Amount >> k.Working_amount >> k.Efficiency;
}


int main() {
    pipeline pipeline_1;
    KC KC_1;
    bool flag = true;
    while (flag) {
        menu();
        int n;
        n = check_int();
        switch (n)
        {
        case 1: {
            pipeline_1 = add_pipeline();
            break;
        }
        case 2: {
            KC_1 = add_KC();
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
                change_pipe(pipeline_1);
                cout << pipeline_1;
            } else {
                cout << "No pipelines" << endl;
            }
            break;
        }
        case 5: {
            if (!KC_1.Name.empty()) {
                change_KC(KC_1);
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
                save_pipeline(out, pipeline_1);
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
                download_pipeline(in, pipeline_1);
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










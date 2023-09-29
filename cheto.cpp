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
    bool flag = true;
    while (flag) {
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

void change_KC(KC& k) {
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
}


KC get_KC_data(KC k) {
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
    return k;
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
    k = get_KC_data(k);
    cout << k;
    return k;
}

void change_pipe(pipeline& p) {
    cout << "Is pipeline working? (Y/n)" << endl;
    p.Status = check_bool();
}


pipeline get_pipe_data(pipeline& p) {
    cout << "Enter pipeline name" << endl;
    p.Name = read_string();
    cout << "Enter pipeline lenght" << endl;
    p.Lenght = check_int();
    cout << "Enter pipeline diameter" << endl;
    p.Diameter = check_int();
    cout << "Is pipeline working? (Y/n)" << endl;
    p.Status = check_bool();
    return p;
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
    p = get_pipe_data(p);
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

void save_pipeline(const pipeline& p) {
    ofstream out;
    out.open("pipes.txt");
    out << p.Name << endl;
    out << p.Lenght << endl;
    out << p.Diameter << endl;
    out << p.Status << endl;
    out.close();
}

void save_KC(const KC& k) {
    ofstream out;
    out.open("KCs.txt");
    out << k.Name << endl;
    out << k.Amount << endl;
    out << k.Working_amount << endl;
    out << k.Efficiency << endl;
    out.close();
}

void download_pipeline(pipeline& p) {
    std::ifstream in("pipes.txt");
    if (in.is_open())
    {
        string name;
        int lenght, diameter;
        bool status;
        in >> ws;
        getline(in, name);
        in >> lenght >> diameter >> status;
        p.Name = name;
        p.Lenght = lenght;
        p.Diameter = diameter;
        p.Status = (status == 1) ? "working" : "repairing";
    }
    in.close();
}

void download_KC(KC& k) {
    std::ifstream in("KCs.txt");
    if (in.is_open())
    {
        string name;
        int amount, work_amount;
        double efficiency;
        in >> ws;
        getline(in, name);
        in >> amount >> work_amount >> efficiency;
        k.Name = name;
        k.Amount = amount;
        k.Working_amount = work_amount;
        k.Efficiency = efficiency;
    }
    in.close();
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
                cout << "No pipeline" << endl;
            }
            break;
        }
        case 5: {
            if (!KC_1.Name.empty()) {
                change_KC(KC_1);
                cout << KC_1;
            } else {
                cout << "No KS" << endl;
            }
            break;
        }
        case 6: {
            save_pipeline(pipeline_1);
            save_KC(KC_1);
            break;
        }
        case 7: {
            download_pipeline(pipeline_1);
            download_KC(KC_1);
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










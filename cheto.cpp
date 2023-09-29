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

void display_KC_data(const KC& k) {
    cout << "-----------------------" << endl;
    cout << "Your KC:" << endl;
    cout << "Name: " << k.Name << endl;
    cout << "Amount of manufactories: " << k.Amount << endl;
    cout << "Amount of working manufactories: " << k.Working_amount << endl;
    cout << "The value of 'efficiency': " << k.Efficiency << endl;
    cout << "-----------------------" << endl;
}

KC add_KC(KC k) {
    k = get_KC_data(k);
    display_KC_data(k);
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

void display_pipe_data(const pipeline& p) {
    cout << "-----------------------" << endl;
    cout << "Your pipeline:" << endl;
    cout << "Name: " << p.Name << endl;
    cout << "Lenght: " << p.Lenght << endl;
    cout << "Diameter: " << p.Diameter << endl;
    cout << "Status: ";
    if (p.Status == 1) {
        cout << "working" << endl;
    } else if (p.Status == 0) {
        cout << "repairing" << endl;
    } else {
        cout << "unknown" << endl;
    }
    cout << "-----------------------" << endl;
}

pipeline add_pipeline(pipeline p) { 
    p = get_pipe_data(p);
    display_pipe_data(p);
    return p;
}

void menu() {
    cout << "1. Add pipeline" << endl;
    cout << "2. Add ceh" << endl;
    cout << "3. Check all elements" << endl;
    cout << "4. Change the pipeline" << endl;
    cout << "5. Change the ceh" << endl;
    cout << "6. Save" << endl;
    cout << "7. Download" << endl;
    cout << "0. Close" << endl;
}

void save(pipeline p, KC k, bool& current_pipeline, bool& current_KC) {
    ofstream out;
    out.open("datas.txt");
    out << p.Name << endl;
    out << p.Lenght << endl;
    out << p.Diameter << endl;
    out << p.Status << endl;
    out << current_pipeline << endl;
    out << k.Name << endl;
    out << k.Amount << endl;
    out << k.Working_amount << endl;
    out << k.Efficiency << endl;
    out << current_KC << endl;
    out.close();
}

void download(pipeline& p, KC& k, bool& current_pipeline, bool& current_KC) {
    std::ifstream in("datas.txt");
    if (in.is_open())
    {
        bool current_status1, current_status2;
        string name1, name2;
        int lenght, diameter, amount, work_amount;
        double efficiency;
        bool status;
        getline(in, name1);
        in >> lenght >> diameter >> status >> current_status1;
        in >> ws;
        getline(in, name2);
        in >> amount >> work_amount >> efficiency >> current_status2;
        p.Name = name1;
        p.Lenght = lenght;
        p.Diameter = diameter;
        p.Status = (status == 1) ? "working" : "repairing";
        current_pipeline = current_status1;
        k.Name = name2;
        k.Amount = amount;
        k.Working_amount = work_amount;
        k.Efficiency = efficiency;
        current_KC = current_status2;
    }
    in.close();
}



int main() {
    bool flag = true;
    bool current_pipeline = false;
    bool current_KC = false;
    menu();
    KC KC_1;
    pipeline pipeline_1;
    while (flag) {
        int n;
        n = check_int();
        switch (n)
        {
        case 1:
            pipeline_1 = add_pipeline(pipeline_1);
            current_pipeline = true;
            menu();
            break;
        case 2:
            KC_1 = add_KC(KC_1);
            current_KC = true;
            menu();
            break;
        case 3:
            if (current_pipeline == 1) {
                display_pipe_data(pipeline_1);
            } else {
                cout << "no pipelines\n";
            }
            if (current_KC == 1) {
                display_KC_data(KC_1);
            } else {
                cout << "no KCs\n";
            }
            menu();
            break;
        case 4:
            change_pipe(pipeline_1);
            display_pipe_data(pipeline_1);
            menu();
            break;
        case 5:
            change_KC(KC_1);
            display_KC_data(KC_1);
            menu();
            break;
        case 6:
            save(pipeline_1, KC_1, current_pipeline, current_KC);
            menu();
            break;
        case 7:
            download(pipeline_1, KC_1, current_pipeline, current_KC);
            if (current_pipeline == 1) {
                display_pipe_data(pipeline_1);
            } else {
                cout << "no pipelines\n";
            }
            if (current_KC == 1) {
                display_KC_data(KC_1);
            } else {
                cout << "no KCs\n";
            }
            menu();
            break;
        case 0:
            flag = false;
            break;    
        default:
            cout << "please, enter suggested numbers" << endl;
            menu();
            break;
        }
    }
    return 0;
}










#include "KC.h"
#include <fstream>


using namespace std;

int KC::NextId = 2;

KC::KC() {
    this->id=NextId;
    NextId += 2;
}

KC::~KC() {
}

void KC::add_KC() {
    cout << "Enter manufactory name" << endl;
    Name = read_string();
    cout << "Enter amount of manufactories" << endl;
    Amount = check_int();
    cout << "Enter amount of working manufactories" << endl;
    bool flag = true;
    while (flag) {
        Working_amount = check_int();
        if (Working_amount <= Amount) {
            flag = false;
        } else {
            cout << "try again" << endl;
        }
    }
    cout << "Enter the value of 'efficiency'" << endl;
    Efficiency = check_double(); 
}

void KC::change_KC()
 {
    cout << "Enter amount of working manufactories" << endl;
    while (1)
     {
        Working_amount = check_int();
        if (Working_amount <= Amount) 
            return;
        cout << "try again" << endl;
    }
 }

ostream& operator << (ostream& out, const KC& k) {
    out << "-----------------------" << endl;
    out << "Your KC:" << endl;
    out << "ID: " << k.getId() << endl;
    out << "Name: " << k.Name <<endl;
    out << "Amount of manufactor ies: " << k.Amount << endl;
    out << "Amount of working manufactories: " << k.Working_amount << endl;
    out << "The value of 'efficiency': " << k.Efficiency << endl;
    out << "-----------------------" << endl;
    return out;
}
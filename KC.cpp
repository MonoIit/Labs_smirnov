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
    cerr << "User entered the name: " << Name << endl;
    cout << "Enter amount of manufactories" << endl;
    Amount = check(Amount);
    cerr << "User enterd the amount of manufactories: " << Amount << endl;
    cout << "Enter amount of working manufactories" << endl;
    while (1) {
        Working_amount = check(Working_amount);
        if (Working_amount <= Amount) {
            cerr << "User entered amount of working manufactories :" << Working_amount << endl;
            break;
        } else {
            cout << "try again" << endl;
            cerr << "User entered incorrect amount of working manufactories :" << Working_amount << ". Should be less then " << Amount << endl;
        }
    }
    cout << "Enter the value of 'efficiency'" << endl;
    Efficiency = check(Efficiency);
    cerr << "User entered efficiency: " << Efficiency << endl; 
}

void KC::change_KC()
 {
    cout << "Enter amount of working manufactories" << endl;
    while (1)
     {
        Working_amount = check(Working_amount);
        if (Working_amount <= Amount) {
            cerr << "User changed amount of working manufactories to " << Working_amount << endl;
            return;
        }
        cout << "try again" << endl;
        cerr << "User entered incorrect amount of working manufactories :" << Working_amount << ". Should be less then " << Amount << endl;
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
    cerr << "User displayed the information of KC with id" << k.getId() << endl;
    return out;
}
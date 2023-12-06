#include "KC.h"
#include "tools.h"
#include <fstream>


using namespace std;

int KC::NextId = 2;

KC::KC() {
    connections = 0;
    this->id=NextId;
    NextId += 2;
}

void KC::create() {
    cout << "Enter manufactory name" << endl;
    Name = read_string();
    cout << "Enter amount of manufactories" << endl;
    Amount = input_value<int>(1);
    cout << "Enter amount of working manufactories" << endl;
    Working_amount = input_value<int>(1, Amount);
    cout << "Enter the value of 'efficiency'" << endl;
    Efficiency = input_value<double>();
}

void KC::change()
 {
    cout << "Enter amount of working manufactories" << endl;
    Working_amount = input_value<int>(0, Amount);
 }

void KC::save(ofstream& out) {
    out << getId() << endl;
    out << Name << endl;
    out << Amount << endl;
    out << Working_amount << endl;
    out << Efficiency << endl;
    out << connections << endl;
}

void KC::download(ifstream& in) {
    int ID;
    in >> ID;
    this->id = ID;
    NextId = (ID >= NextId) ? (ID) : (NextId);
    in >> ws;
    getline(in, Name);
    in >> ws;
    in >> Amount >> Working_amount >> Efficiency >> connections;
}

ostream& operator << (ostream& out, const KC& k) {
    out << "-----------------------" << endl;
    out << "Your KC:" << endl;
    out << "ID: " << k.getId() << endl;
    out << "Name: " << k.Name <<endl;
    out << "Amount of manufactories: " << k.Amount << endl;
    out << "Amount of working manufactories: " << k.Working_amount << endl;
    out << "The value of 'efficiency': " << k.Efficiency << endl;
    out << "Connected pipes: " << k.connections << endl;
    out << "-----------------------" << endl;
    return out;
}

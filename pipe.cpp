#include "pipe.h"
#include <fstream>
#include "tools.h"

using namespace std;

int Pipe::NextId = 1;

Pipe::Pipe()
{
    this->id=NextId;
    NextId += 2;
}

Pipe::~Pipe(){
}

void Pipe::add_pipe() {
    cout << "Enter pipeline name" << endl;
    Name = read_string();
    cerr << "User entered the name: " << Name << endl;
    cout << "Enter pipeline lenght" << endl;
    Lenght = check_int();
    cerr << "User entered the Lenght: " << Lenght << endl;
    cout << "Enter pipeline diameter" << endl;
    Diameter = check_int();
    cerr << "User entered the Diameter: " << Diameter << endl;
    cout << "Is pipeline working? (Y/n)" << endl;
    Status = check_bool();
    cerr << "User chose " << ((Status == 1) ? "working" : "repairing") << "pipe" << endl;
}

void Pipe::change_pipe() {
    Status = (Status == 1) ? 0 : 1;
    cerr << "User changed pipe with id " << getId() << ". Status: " << ((Status == 1) ? "working" : "repairing") << endl;
}

ostream& operator << (ostream& out, const Pipe& p) {
    out << "-----------------------" << endl;
    out << "Your pipeline:" << endl;
    out << "ID: " << p.getId() << endl; 
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
    cerr << "User displayed the information of pipe with id" << p.getId() << endl;
    return out;
}


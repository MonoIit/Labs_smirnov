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

void Pipe::add_pipe() {
    cout << "Enter pipeline name" << endl;
    Name = read_string();
    cout << "Enter pipeline lenght" << endl;
    Lenght = check_int();
    cout << "Enter pipeline diameter" << endl;
    Diameter = check_int();
    cout << "Is pipeline working? (Y/n)" << endl;
    Status = check_bool();
}

void Pipe::change_pipe() {
    Status = (Status == 1) ? 0 : 1;
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
    return out;
}


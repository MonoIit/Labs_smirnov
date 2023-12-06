#include "pipe.h"
#include <fstream>
#include "tools.h"

using namespace std;

int Pipe::NextId = 1;

Pipe::Pipe()
{
    connect_status = false;
    connect_to = -1;
    connect_from = -1;
    this->id=NextId;
    NextId += 2;
}

void Pipe::create() {
    cout << "Enter pipeline name" << endl;
    Name = read_string();
    cout << "Enter pipeline lenght" << endl;
    Lenght = input_value<int>(1);
    cout << "Enter pipeline diameter" << endl;
    Diameter = input_diameter();
    cout << "Is pipeline working? (1/0)" << endl;
    Status = input_value<bool>();
}

void Pipe::change() {
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
    if (p.connect_status)
    {
        out << "Connected from" << p.connect_from << endl;
        out << "Connected to" << p.connect_to << endl;
    }
    else 
    {
        out << "No connection" << endl;
    }
    out << "-----------------------" << endl;
    return out;
}

void Pipe::save(ofstream& out) {
    out << getId() << endl;
    out << Name << endl;
    out << Lenght << endl;
    out << Diameter << endl;
    out << Status << endl;
    out << connect_status << endl;
    out << connect_from << endl;
    out << connect_to << endl;
}

void Pipe::download(ifstream& in) {
    {
        int ID;
        in >> ID;
        this->id = ID;
        NextId = (ID >= NextId) ? (ID) : (NextId);
        in >> ws;
        getline(in, Name);
        in >> ws;
        in >> Lenght >> Diameter >> Status >> connect_status >> connect_from >> connect_to;
    }
}

void Pipe::connect(int to, int from)
{
    connect_status = true;
    connect_to = to;
    connect_from = from;
}

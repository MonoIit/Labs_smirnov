#include <iostream>
#include <fstream>
#include <string>
#include "tools.h"

using namespace std;

class Pipe {
    int id;
    static int NextId;
public:
    int getId() const {return id; }
    string Name;
    int Lenght;
    int Diameter;
    bool Status;
    Pipe();
    void add_pipe();
    void change_pipe();
    friend ostream& operator << (ostream& out, const Pipe& p);
};



inline void save_pipe(ofstream& out, const Pipe& p) {
    out << p.Name << endl;
    out << p.Lenght << endl;
    out << p.Diameter << endl;
    out << p.Status << endl;
}

inline void download_pipe(ifstream& in, Pipe& p) {
    {
        getline(in, p.Name);
        in >> ws;
        in >> p.Lenght >> p.Diameter >> p.Status;
    }
}
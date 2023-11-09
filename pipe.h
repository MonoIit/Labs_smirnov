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
    void save_pipe(ofstream& out);
    void download_pipe(ifstream& in);
    friend ostream& operator << (ostream& out, const Pipe& p);
};



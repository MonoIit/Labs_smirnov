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
    bool connect_status;
    int connect_from;
    int connect_to;
    Pipe();
    void create();
    void change();
    void save(ofstream& out);
    void download(ifstream& in);
    friend ostream& operator << (ostream& out, const Pipe& p);
    void connect(int in, int out);
};



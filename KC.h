#include <iostream>
#include <fstream>
#include <string>
#include "tools.h"

using namespace std;

class KC {
    int id;
    static int NextId;
public:
    int getId() const {return id; }
    string Name;
    int Amount;
    int Working_amount;
    double Efficiency;
    KC();
    void add_KC();
    void change_KC();
    friend ostream& operator << (ostream& out, const KC& m);
};

inline void save_KC(ofstream& out, const KC& k) {
    out << k.Name << endl;
    out << k.Amount << endl;
    out << k.Working_amount << endl;
    out << k.Efficiency << endl;
}



inline void download_KC(ifstream& in, KC& k) {
    getline(in, k.Name);
    in >> k.Amount >> k.Working_amount >> k.Efficiency;
}

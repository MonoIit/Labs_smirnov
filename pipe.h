#pragma once
#include <iostream>
#include <fstream>
#include <string>

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
    int connect_from;
    int connect_to;
    Pipe();
    void create();
    void create(int& diameter);
    void change();
    void save(ofstream& out);
    void download(ifstream& in);
    void createLink(int &from, int &to);
    void removeLink();
    bool linked();
    void showLink();
    friend ostream& operator << (ostream& out, const Pipe& p);
};



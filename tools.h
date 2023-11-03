#pragma once
#include <iostream>
#include <string>

using namespace std;

#define printpar(out, mas) out << "no " << #mas << endl;

template <typename T>
inline T check(T a) {
    T value = a;
    cin >> value;
    while (cin.fail() || cin.peek() != '\n' || value < 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "try again" << endl;
        cin >> value;
    }
    return value;
}

inline string read_string() {
    string name;
    cin >> ws;
    getline(cin, name);
    return name;
}   

/*inline int check_int() {
    int value;
    cin >> value;
    while (cin.fail() || std::cin.peek() != '\n' || value < 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "try again" << endl;
        cin >> value;
    }
    return value;
}

inline double check_double() {
    double value;
    cin >> value;
    while (cin.fail() || std::cin.peek() != '\n' || value < 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "try again" << endl;
        cin >> value;
    }
    return value;
}

inline bool check_bool() {
    char value;
    cin >> value;
    while (1) 
    {
        if (value == 'n') {
            return 0;
        } else if (value == 'Y') {
            return 1;
        } else {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Enter Y/n" << endl;
            cin >> value;
        }
    }
}*/

class redirect_output_wrapper
{
    std::ostream& stream;
    std::streambuf* const old_buf;
public:
	redirect_output_wrapper(std::ostream& src)
		:old_buf(src.rdbuf()), stream(src)
    {
    }

    ~redirect_output_wrapper() {
		stream.rdbuf(old_buf);
    }
	void redirect (std::ostream& dest)
	{
		stream.rdbuf(dest.rdbuf());
	}
};
#pragma once
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <string>
#include <limits>
#include <vector>


using namespace std;

#define printpar(out, mas) out << "no " << #mas << std::endl;

template <typename T>
T input_value(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max()) {
    T value;
    std::cin >> value;
    while (std::cin.fail() || std::cin.peek() != '\n' || value < min || value>max) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "try again" << std::endl;
        std::cin >> value;
    }
    std::cerr << value << std::endl;
    return value;
}

inline bool have(int value, vector<int> &values)
{
    for (int i = 0; i < 4; i++)
        if (values[i] == value)
            return 1;
    return 0;
}

template <typename T>
inline int search(int &id, const T &mas)
{
    if (mas.find(id) != mas.end())
        return id;
    return -1;
}

inline bool search(int& id, vector<int>& mas)
{
    vector<int>::iterator iter;
    for (iter = mas.begin(); iter != mas.end(); iter++)
        if (mas[*iter] == id)
            return 1;
    return 0;
}

inline int input_diameter() {
    int valu;
    vector<int> values;
    values.push_back(500);
    values.push_back(700);
    values.push_back(1000);
    values.push_back(1400);
    std::cin >> valu;
    while (std::cin.fail() || std::cin.peek() != '\n' || !have(valu, values))
    {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "try again" << std::endl;
        std::cin >> valu;
    }
    std::cerr << valu << std::endl;
    return valu;
}

inline std::string read_string() {
    std::string name;
    std::cin >> std::ws;
    std::getline(std::cin, name);
    std::cerr << name << std::endl;
    return name;
}   

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



inline void input_id(int &id, unordered_set<int>& loll)
{
    id = input_value<int>(0);
    while (1)
    {
        if (search(id, loll))
        {
            break;
        }
        else
        {
            cout << "No object with this id" << endl;
            id = input_value<int>(0);
        }
    }
}

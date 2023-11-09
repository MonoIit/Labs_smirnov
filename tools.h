#pragma once
#include <iostream>
#include <string>
#include <limits>



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
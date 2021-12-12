#ifndef LIB_HPP
#define LIB_HPP


#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

vector<string> parse(string input, string delimiter);
template<class T> ostream& operator<<(ostream& lhs, vector<T>& rhs);

class Displays {
public:
    vector<string> patterns;
    vector<string> outputs;
    int basicDigitsCount; // How many 1, 4, 7 and 8 appears.

    Displays(string entry);
    void toConsole();
};


#endif

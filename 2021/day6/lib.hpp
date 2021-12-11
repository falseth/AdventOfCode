#ifndef LIB_HPP
#define LIB_HPP


#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

class Int;

vector<string> parse(string input, string delimiter);

class Lanternfishes {
public:
    vector<int> lanternfishes;
    vector<Int> quickCount;
    ofstream file;
    int daysElapsed;
    bool fastMode;
    bool doesOutput;

    Lanternfishes(vector<string> lanternfishes, bool fastMode, bool doesOutput);
    void advance();
    void advance(int days);
    void output();
    string toString();
    Int size();
    void close();
};

class Int {
public:
    string num; // The number itself is a string (no '-' or '+').
    bool sign;  // 0 = positive or zero, 1 = negative.
    long size;  // num.size().

    Int();
    Int(int num);
    void operator++(int);
    void operator+=(Int& rhs);
    void operator-=(Int& rhs);
    friend int uCmp(Int& lhs, Int& rhs);
    friend bool operator<(Int& lhs, Int& rhs);
    friend basic_ostream<char>& operator<<(basic_ostream<char>& lhs, Int& rhs);
};


#endif

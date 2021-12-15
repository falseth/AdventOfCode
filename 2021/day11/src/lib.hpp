#ifndef LIB_HPP
#define LIB_HPP


#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>
#include <iterator>
#include "EasyBMP.h"

using namespace std;

class Int;

vector<string> parse(string input, string delimiter);
template<class T> ostream& operator<<(ostream& lhs, vector<T>& rhs);
ostream& operator<<(ostream& lhs, vector<int> rhs);
vector<int> max(vector<int>& nums, int n = 1);
vector<Int> max(vector<Int>& nums, int n = 1);
void draw(BMP& image, int i, int j, int r = 255, int g = 0, int b = 0, int a = 255);

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
    void operator*=(Int& rhs);
    friend int uCmp(Int& lhs, Int& rhs);
    friend bool operator<(Int& lhs, Int& rhs);
    friend basic_ostream<char>& operator<<(basic_ostream<char>& lhs, Int& rhs);
};

class Point {
public:
    int x, y;

    Point();
    Point(const int x, const int y);
    friend bool operator==(Point& lhs, Point& rhs);
    friend ostream& operator<<(ostream& lhs, Point rhs);
};

class Octopusses {
public:
    Octopusses(vector<string> energyLevels);
    void advance();
    void advance(int steps);
    void advanceUntilSync();
    void output();

private:
    vector<vector<int>> energyLevels;
    int steps;
    int flashes;

    vector<Point> findNeighbors(Point& point);
};


#endif

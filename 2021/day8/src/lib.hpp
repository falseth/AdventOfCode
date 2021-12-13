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

vector<string> parse(string input, string delimiter);
template<class T> ostream& operator<<(ostream& lhs, vector<T>& rhs);
template<class T> vector<T> operator-(vector<T>& lhs, vector<T>& rhs);
string operator-(string& lhs, string& rhs);
void draw(BMP& image, int i, int j, int r = 255, int g = 0, int b = 0, int a = 255);
void drawDisplay(char num, BMP& image, int i, int j, int r = 255, int g = 0, int b = 0, int a = 255);
vector<bool> highlightSegments(char num);

class Displays {
public:
    vector<string> patterns;
    vector<string> outputs;
    int basicDigitsCount; // How many 1, 4, 7 and 8 appears.
    string output;
    string one, four, seven, eight;
    string zero, two, three, five, six, nine;
    vector<string> twoThreeFive, zeroSixNine;
    char a, b, c, d, e, f, g;

    Displays(string entry);
    string decode();
    void toConsole();
};


#endif

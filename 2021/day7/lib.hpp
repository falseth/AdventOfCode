#ifndef LIB_HPP
#define LIB_HPP


#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

vector<string> parse(string input, string delimiter);

class Crabs {
public:
    vector<int> positions;
    vector<int> crabsCount;
    int min, max;
    int lowestPosition, lowestScore;

    Crabs(vector<string>& positions);
    void toConsole();
};

#endif

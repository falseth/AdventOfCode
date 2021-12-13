#ifndef LIB_HPP
#define LIB_HPP


#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>
#include <iterator>

using namespace std;

vector<string> parse(string input, string delimiter);
template<class T> ostream& operator<<(ostream& lhs, vector<T>& rhs);

class Map {
public:
    vector<vector<int>> heightMap;

    Map(vector<string> heightMap);
};


#endif

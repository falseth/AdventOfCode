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
ostream& operator<<(ostream& lhs, vector<int> rhs);
void draw(BMP& image, int i, int j, int r = 255, int g = 0, int b = 0, int a = 255);
vector<int> max(vector<int>& nums, int n = 1);

class Point {
public:
    int x, y;

    Point();
    Point(const int x, const int y);
    friend bool operator==(Point& lhs, Point& rhs);
    friend ostream& operator<<(ostream& lhs, Point rhs);
};

class Map {
public:
    Map(vector<string> heightMap);
    void output();

private:
    vector<vector<int>> heightMap;
    vector<Point> lowPoints, basinBorders;
    vector<vector<Point>> basins;
    int riskLevels;

    void countRiskLevels();
    void findLowPoints();
    void findBasins();
    vector<Point> findBasin(Point& lowPoint);
    vector<Point> findNeighbors(Point& point);
};


#endif

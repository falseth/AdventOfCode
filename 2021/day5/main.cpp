#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include "EasyBMP.h"

using namespace std;

vector<string> parse(string input, string delimiter);

class Point {
public:
    int x, y;

    Point() {
        this->x = 0;
        this->y = 0;
    }

    Point(const int x, const int y) {
        this->x = x;
        this->y = y;
    }

    string to_string() {
        string output;
        output += std::to_string(x);
        output += ",";
        output += std::to_string(y);
        return output;
    }
};

class Line {
public:
    Point start, end;
    vector<Point> points;

    Line() {
        this->start = Point();
        this->end = Point();

        points.push_back(this->start);
    }

    Line(const Point& start, const Point& end) {
        this->start = start;
        this->end = end;

        if (this->start.x == this->end.x && this->start.y < this->end.y) {
            for (int i = this->start.y; i <= this->end.y; i++) {
                points.push_back(Point(this->start.x, i));
            }
        } else if (this->start.x == this->end.x && this->start.y > this->end.y) {
            for (int i = this->start.y; i >= this->end.y; i--) {
                points.push_back(Point(this->start.x, i));
            }
        } else if (this->start.x < this->end.x && this->start.y == this->end.y) {
            for (int i = this->start.x; i <= this->end.x; i++) {
                points.push_back(Point(i, this->start.y));
            }
        } else if (this->start.x > this->end.x && this->start.y == this->end.y) {
            for (int i = this->start.x; i >= this->end.x; i--) {
                points.push_back(Point(i, this->start.y));
            }
        } else if (this->start.x == this->end.x && this->start.y == this->end.y) {
            points.push_back(Point(this->start.x, this->start.y));
        }
    }

    void to_console() {
        cout << start.to_string() << " -> " << end.to_string() << endl;
    }
};

class Map {
public:
    int length, width;
    int overlaps;
    vector<Line> lines;
    vector<vector<int>> map;

    Map(const int length, const int width) {
        this->length = length;
        this->width = width;
        this->overlaps = 0;
        this->map = vector<vector<int>>(width, vector<int>(length, 0));
    }

    void add_line(const Line& line) {
        lines.push_back(line);

        for (Point point : line.points) {
            this->map[point.y][point.x]++;
        }

        this->check();
    }

    void to_console() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        for (int i = 0; i < this->width; i++) {
            for (int j = 0; j < this->length; j++) {
                if (this->map[i][j] >= 2) {
                    SetConsoleTextAttribute(hConsole, 0x0C);
                } else {
                    SetConsoleTextAttribute(hConsole, 0x0F);
                }
                cout << this->map[i][j];

                SetConsoleTextAttribute(hConsole, 0x0F);
                cout << " ";
            }
            SetConsoleTextAttribute(hConsole, 0x0F);
            cout << endl;
        }

        SetConsoleTextAttribute(hConsole, 0x0F);
        cout << "There are " << this->overlaps << " points where at least two lines overlap." << endl;
    }

private:
    void check() {
        this->overlaps = 0;
        for (int i = 0; i < this->width; i++) {
            for (int j = 0; j < this->length; j++) {
                if (this->map[i][j] >= 2) {
                    this->overlaps++;
                }
            }
        }
    }
};

int main(void) {
    BMP AnImage;
    // Set size to 640 × 480
    AnImage.SetSize(640,480);
    // Set its color depth to 32-bits
    AnImage.SetBitDepth(32);

    // Set one of the pixels
    AnImage(14,18)->Red = 255;
    AnImage(14,18)->Green = 255;
    AnImage(14,18)->Blue = 255;
    AnImage(14,18)->Alpha = 0;

    AnImage.WriteToFile("Output.bmp");

    ifstream file;
    file.open("test.txt");

    if (!file.is_open()) {
        cout << "AN ERROR HAS OCCURRED" << endl;
        return 1;
    }

    string line;
    vector<string> input;
    while (getline(file, line)) {
        input.push_back(line);
    }
    file.close();

    Map map(10, 10);
    for (string line : input) {
        Point start(stoi(parse(parse(line, " -> ")[0], ",")[0]), stoi(parse(parse(line, " -> ")[0], ",")[1]));
        Point end(stoi(parse(parse(line, " -> ")[1], ",")[0]), stoi(parse(parse(line, " -> ")[1], ",")[1]));

        map.add_line(Line(start, end));
    }
    map.to_console();
    cout << map.overlaps << endl;

    return 0;
}

vector<string> parse(string input, string delimiter) {
    size_t pos = 0;
    string token;
    vector<string> output;

    while ((pos = input.find(delimiter)) == 0) {
        input.erase(0, delimiter.length());
    }

    while ((pos = input.find(delimiter)) != string::npos) {
        token = input.substr(0, pos);
        output.push_back(token);
        input.erase(0, pos + delimiter.length());

        while ((pos = input.find(delimiter)) == 0) {
            input.erase(0, delimiter.length());
        }
    }
    output.push_back(input);

    return output;
}
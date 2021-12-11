#include <iostream>
#include <fstream>
#include <vector>
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
        } else if (this->start.x > this->end.x && this->start.y > this->end.y) {
            for (int i = this->start.x; i >= this->end.x; i--) {
                points.push_back(Point(i, this->start.y - this->start.x + i));
            }
        } else if (this->start.x > this->end.x && this->start.y < this->end.y) {
            for (int i = this->start.x; i >= this->end.x; i--) {
                points.push_back(Point(i, this->start.y + this->start.x - i));
            }
        } else if (this->start.x < this->end.x && this->start.y > this->end.y) {
            for (int i = this->start.x; i <= this->end.x; i++) {
                points.push_back(Point(i, this->start.y + this->start.x - i));
            }
        } else if (this->start.x < this->end.x && this->start.y < this->end.y) {
            for (int i = this->start.x; i <= this->end.x; i++) {
                points.push_back(Point(i, this->start.y - this->start.x + i));
            }
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

    void output() {
        BMP image;
        image.SetSize(this->length, this->width);
        image.SetBitDepth(32);
        for (int i = 0; i < this->width; i++) {
            for (int j = 0; j < this->length; j++) {
                if (this->map[i][j] >= 2) {
                    image(j, i)->Red = 255;
                    image(j, i)->Green = 0;
                    image(j, i)->Blue = 0;
                    image(j, i)->Alpha = 255;
                }
            }
        }
        image.WriteToFile("output.bmp");

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
    ifstream file;
    file.open("input.txt");

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

    int length = 1000, width = 1000;
    Map map(length, width);
    for (string line : input) {
        Point start(stoi(parse(parse(line, " -> ")[0], ",")[0]), stoi(parse(parse(line, " -> ")[0], ",")[1]));
        Point end(stoi(parse(parse(line, " -> ")[1], ",")[0]), stoi(parse(parse(line, " -> ")[1], ",")[1]));

        map.add_line(Line(start, end));
    }

    map.output();
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
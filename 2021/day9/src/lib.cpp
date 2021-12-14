#include "lib.hpp"

using namespace std;

// https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
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

// https://stackoverflow.com/questions/33665257/how-to-overload-ostream-for-vector-to-print-all-collection-from-vector
template<class T> ostream& operator<<(ostream& lhs, vector<T>& rhs) {
    lhs << "[";
    for (int i = 0; i < rhs.size() - 1; i++) {
        cout << rhs[i] << ", ";
    }

    if (rhs.size() - 1 >= 0) {
        cout << rhs[rhs.size() - 1];
    }
    lhs << "]";
    return lhs;
}

ostream& operator<<(ostream& lhs, vector<int> rhs) {
    lhs << "[";
    for (int i = 0; i < rhs.size() - 1; i++) {
        cout << rhs[i] << ", ";
    }

    if (rhs.size() - 1 >= 0) {
        cout << rhs[rhs.size() - 1];
    }
    lhs << "]";
    return lhs;
}

void draw(BMP& image, int i, int j, int r, int g, int b, int a) {
    image(i, j)->Red = r;
    image(i, j)->Green = g;
    image(i, j)->Blue = b;
    image(i, j)->Alpha = a;
}

vector<int> max(vector<int>& nums, int n) {
    vector<int> output(n, 0);

    for (int num : nums) {
        for (int i = 0; i < n; i++) {
            if (output[i] < num) {
                output.insert(output.begin()+i, num);
                output.pop_back();
                break;
            }
        }
    }

    return output;
}

Point::Point() {
    this->x = 0;
    this->y = 0;
}

Point::Point(const int x, const int y) {
    this->x = x;
    this->y = y;
}

bool operator==(Point& lhs, Point& rhs) {
    return (lhs.x == rhs.x && lhs.y == rhs.y);
}

ostream& operator<<(ostream& lhs, Point rhs) {
    lhs << "(" << rhs.x << ", " << rhs.y << ")";
    return lhs;
}

Map::Map(vector<string> heightMap) {
    int rows = heightMap.size();
    int cols = heightMap[0].size();

    this->heightMap = vector<vector<int>>(rows, vector<int>(cols));
    for (int i = 0; i < heightMap.size(); i++) {
        for (int j = 0; j < heightMap[i].size(); j++) {
            if (heightMap[i][j] == '9') {
                this->basinBorders.push_back(Point(j, i));
            }
            this->heightMap[i][j] = heightMap[i][j] - '0';
        }
    }

    this->findLowPoints();
    this->findBasins();
    this->countRiskLevels();
}

void Map::output() {
    BMP image;
    image.SetSize(this->heightMap[0].size(), this->heightMap.size());
    image.SetBitDepth(32);

    for (int i = 0; i < this->heightMap.size(); i++) {
        for (int j = 0; j < this->heightMap[i].size(); j++) {
            int val = (9 - this->heightMap[i][j]) * 255 / 9;
            draw(image, j, i, val, val, val);
        }
    }
    image.WriteToFile("bin/heightMap.bmp");

    for (Point point : this->basinBorders) {
        draw(image, point.x, point.y, 0);
    }
    vector<int> basinSizes;
    for (vector<Point> points : this->basins) {
        basinSizes.push_back(points.size());
        for (Point point : points) {
            draw(image, point.x, point.y, 0, 255);
        }
    }
    for (Point point : this->lowPoints) {
        draw(image, point.x, point.y);
    }
    image.WriteToFile("bin/basins.bmp");

    cout << "The sum of the risk levels of all low points on the heightmap is " << this->riskLevels << "." << endl;

    vector<int> topBasinSizes = max(basinSizes, 3);
    cout << "The top " << topBasinSizes.size() << " basin sizes are " << topBasinSizes << "." << endl;

    int product = 1;
    for (int num : topBasinSizes) {
        product *= num;
    }
    cout << "The product of those is " << product << "." << endl;
}

void Map::countRiskLevels() {
    this->riskLevels = 0;
    for (Point point : this->lowPoints) {
        this->riskLevels += this->heightMap[point.y][point.x] + 1;
    }
}

void Map::findLowPoints() {
    int i, j, tmp, up, down, left, right;

    // Middle Points
    for (i = 1; i < this->heightMap.size() - 1; i++) {
        for (j = 1; j < this->heightMap[i].size() - 1; j++) {
            tmp = this->heightMap[i][j];
            up = this->heightMap[i - 1][j];
            down = this->heightMap[i + 1][j];
            left = this->heightMap[i][j - 1];
            right = this->heightMap[i][j + 1];
            if (tmp < up && tmp < down && tmp < left && tmp < right) {
                this->lowPoints.push_back(Point(j, i));
            }
        }
    }

    // Upper Edge Points
    for (j = 1; j < this->heightMap[0].size() - 1; j++) {
        i = 0;
        tmp = this->heightMap[i][j];
        down = this->heightMap[i + 1][j];
        left = this->heightMap[i][j - 1];
        right = this->heightMap[i][j + 1];
        if (tmp < down && tmp < left && tmp < right) {
            this->lowPoints.push_back(Point(j, i));
        }
    }

    // Lower Edge Points
    for (j = 1; j < this->heightMap[0].size() - 1; j++) {
        i = this->heightMap.size() - 1;
        tmp = this->heightMap[i][j];
        up = this->heightMap[i - 1][j];
        left = this->heightMap[i][j - 1];
        right = this->heightMap[i][j + 1];
        if (tmp < up && tmp < left && tmp < right) {
            this->lowPoints.push_back(Point(j, i));
        }
    }

    // Left Edge Points
    for (i = 1; i < this->heightMap.size() - 1; i++) {
        j = 0;
        tmp = this->heightMap[i][j];
        up = this->heightMap[i - 1][j];
        down = this->heightMap[i + 1][j];
        right = this->heightMap[i][j + 1];
        if (tmp < up && tmp < down && tmp < right) {
            this->lowPoints.push_back(Point(j, i));
        }
    }

    // Right Edge Points
    for (i = 1; i < this->heightMap.size() - 1; i++) {
        j = this->heightMap[i].size() - 1;
        tmp = this->heightMap[i][j];
        up = this->heightMap[i - 1][j];
        down = this->heightMap[i + 1][j];
        left = this->heightMap[i][j - 1];
        if (tmp < up && tmp < down && tmp < left) {
            this->lowPoints.push_back(Point(j, i));
        }
    }

    // Upper Left Corner
    i = 0;
    j = 0;
    tmp = this->heightMap[i][j];
    down = this->heightMap[i + 1][j];
    right = this->heightMap[i][j + 1];
    if (tmp < down && tmp < right) {
        this->lowPoints.push_back(Point(j, i));
    }

    // Upper Right Corner
    i = 0;
    j = this->heightMap[0].size() - 1;
    tmp = this->heightMap[i][j];
    down = this->heightMap[i + 1][j];
    left = this->heightMap[i][j - 1];
    if (tmp < down && tmp < left) {
        this->lowPoints.push_back(Point(j, i));
    }

    // Lower Left Corner
    i = this->heightMap.size() - 1;
    j = 0;
    tmp = this->heightMap[i][j];
    up = this->heightMap[i - 1][j];
    right = this->heightMap[i][j + 1];
    if (tmp < up && tmp < right) {
        this->lowPoints.push_back(Point(j, i));
    }

    // Lower Right Corner
    i = this->heightMap.size() - 1;
    j = this->heightMap[i].size() - 1;
    tmp = this->heightMap[i][j];
    up = this->heightMap[i - 1][j];
    left = this->heightMap[i][j - 1];
    if (tmp < up && tmp < left) {
        this->lowPoints.push_back(Point(j, i));
    }
}

void Map::findBasins() {
    for (Point lowPoint : this->lowPoints) {
        this->basins.push_back(this->findBasin(lowPoint));
    }
}

vector<Point> Map::findBasin(Point& lowPoint) {
    vector<Point> output;
    vector<Point> stack;

    stack.push_back(lowPoint);
    while (!stack.empty()) {
        Point point = stack.back();
        stack.pop_back();

        if (this->heightMap[point.y][point.x] != 9) {
            output.push_back(point);
            vector<Point> neighbors = this->findNeighbors(point);

            int i, j;
            for (Point neighbor : neighbors) {
                for (i = 0; i < output.size(); i++) {
                    if (output[i] == neighbor) {
                        break;
                    }
                }

                for (j = 0; j < stack.size(); j++) {
                    if (stack[j] == neighbor) {
                        break;
                    }
                }

                if (i == output.size() && j == stack.size()) {
                    stack.push_back(neighbor);
                }
            }
        }
    }

    return output;
}

vector<Point> Map::findNeighbors(Point& point) {
    vector<Point> output;

    // Left Neighbor
    if (point.x > 0) {
        output.push_back(Point(point.x-1, point.y));
    }

    // Right Neighbor
    if (point.x < this->heightMap[point.y].size()-1) {
        output.push_back(Point(point.x+1, point.y));
    }

    // Upper Neighbor
    if (point.y > 0) {
        output.push_back(Point(point.x, point.y-1));
    }

    // Lower Neighbor
    if (point.y < this->heightMap.size()-1) {
        output.push_back(Point(point.x, point.y+1));
    }

    return output;
}

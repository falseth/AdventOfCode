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

vector<Int> max(vector<Int>& nums, int n) {
    vector<Int> output(n, Int(0));

    for (Int num : nums) {
        for (long i = 0; i < n; i++) {
            if (uCmp(output[i], num) < 0) {
                output.insert(output.begin()+i, num);
                output.pop_back();
                break;
            }
        }
    }

    return output;
}

void draw(BMP& image, int i, int j, int r, int g, int b, int a) {
    image(i, j)->Red = r;
    image(i, j)->Green = g;
    image(i, j)->Blue = b;
    image(i, j)->Alpha = a;
}

Int::Int() {
    Int(0);
}

Int::Int(int num) {
    if (num >= 0) {
        this->sign = 0;
        this->num = to_string(num);
        this->size = this->num.size();
    }
    else {
        this->sign = 1;
        this->num = to_string(num).substr(1, string::npos);
        this->size = this->num.size();
    }
}

void Int::operator++(int) {
    Int num(1);
    this->operator+=(num);
}

void Int::operator+=(Int& rhs) {
    if (this->sign != rhs.sign) {
        Int tmp(rhs);
        tmp.sign = !tmp.sign;
        this->operator-=(tmp);
    }

    Int& big = (this->size > rhs.size) ? (*this) : rhs;
    Int& small = (this->size > rhs.size) ? rhs : (*this);

    long tmp, carry = 0;
    string num(big.size + 2, '0');

    for (long i = 0; i < small.size; i++) {
        tmp = big.num[big.size - i - 1] + small.num[small.size - i - 1] + carry - 2 * '0';
        carry = tmp / 10;
        num[big.size - i] = tmp % 10 + '0';
    }

    for (long i = small.size; i < big.size; i++) {
        tmp = big.num[big.size - i - 1] + carry - '0';
        carry = tmp / 10;
        num[big.size - i] = tmp % 10 + '0';
    }

    num[big.size + 1] = '\0';
    if (carry == 0) {
        for (long i = 0; i < big.size + 1; i++) {
            num[i] = num[i + 1];
        }
        num.pop_back();
    }
    else {
        num[0] = '1';
    }

    this->num = num;
    this->size = big.size + carry;
    if (this->num[0] == '0') {
        this->sign = 0;
    }
}

void Int::operator-=(Int& rhs) {
    if (this->sign != rhs.sign) {
        Int tmp(rhs);
        tmp.sign = !tmp.sign;
        this->operator+=(tmp);
    }

    Int& big = (this->size > rhs.size) ? (*this) : rhs;
    Int& small = (this->size > rhs.size) ? rhs : (*this);

    bool sign;
    if (uCmp(*this, rhs) > 0) {
        sign = this->sign;
    }
    else {
        sign = !rhs.sign;
    }

    long tmp, borrow = 0;
    string num(big.size + 1, '0');

    for (long i = 0; i < small.size; i++) {
        tmp = 10 + big.num[big.size - i - 1] - small.num[small.size - i - 1] - borrow;
        borrow = !(tmp / 10);
        num[big.size - i - 1] = tmp % 10 + '0';
    }

    for (long i = small.size; i < big.size; i++) {
        tmp = 10 + big.num[big.size - i - 1] - borrow - '0';
        borrow = !(tmp / 10);
        num[big.size - i - 1] = tmp % 10 + '0';
    }

    num[big.size] = '\0';
    for (tmp = 0; tmp < big.size - 1; tmp++) {
        if (num[tmp] != '0') {
            break;
        }
    }

    for (long i = tmp; i <= big.size; i++) {
        num[i - tmp] = num[i];
    }

    num.resize(big.size + 1 - tmp);

    this->num = num;
    this->size = big.size - tmp;
    if (this->num[0] == '0') {
        this->sign = 0;
    }
    else {
        this->sign = sign;
    }
}

void Int::operator*=(Int& rhs) {
    if (this->num[0] == '0' || rhs.num[0] == '0') {
        this->num = "0";
        this->size = 1;
        this->sign = false;
        return;
    }

    Int result = Int(0);
    for (long i = 0; i < rhs.size; i++) {
        Int tmp = Int(0);
        for (long j = 0; j < rhs.num[rhs.size - i - 1] - '0'; j++) {
            tmp += (*this);
        }

        tmp.num.resize(tmp.size + i + 1);
        for (long j = tmp.size; j < tmp.size + i; j++) {
            tmp.num[j] = '0';
        }
        tmp.num[tmp.size + i] = '\0';
        tmp.size += i;

        result += tmp;
    }

    this->num = result.num;
    this->size = result.size;
    this->sign = (this->sign == rhs.sign) ? false : true;
}

int uCmp(Int& lhs, Int& rhs) {
    // Test size
    if (lhs.size > rhs.size) {
        return 1;
    }
    else if (lhs.size < rhs.size) {
        return -1;
    }
    else {
        // Test the first digit difference
        long i;
        for (i = 0; i < lhs.size; i++) {
            if (lhs.num[i] != rhs.num[i]) {
                break;
            }
        }

        if (i == lhs.size) {
            return 0;
        }
        else if (lhs.num[i] > rhs.num[i]) {
            return 1;
        }
        else {
            return -1;
        }
    }
}

bool operator<(Int& lhs, Int& rhs) {
    // Test signs
    if (lhs.sign == 0 && rhs.sign == 1) {
        return false;
    }
    else if (lhs.sign == 1 && rhs.sign == 0) {
        return true;
    }

    // Test size (assuming positive)
    bool tmp = uCmp(lhs, rhs);

    // Flip the sign if lhs and rhs are negative
    if (lhs.sign == 0) {
        return tmp;
    } else {
        return -tmp;
    }
}

ostream& operator<<(ostream& lhs, Int& rhs) {
    if (rhs.sign == 1) {
        lhs << "-";
    }
    lhs << rhs.num;
    return lhs;
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

Octopusses::Octopusses(vector<string> energyLevels) {
    int rows = energyLevels.size();
    int cols = energyLevels[0].size();

    this->energyLevels = vector<vector<int>>(rows, vector<int>(cols));
    for (int i = 0; i < energyLevels.size(); i++) {
        for (int j = 0; j < energyLevels[i].size(); j++) {
            this->energyLevels[i][j] = energyLevels[i][j] - '0';
        }
    }

    this->steps = 0;
    this->flashes = 0;
    this->output();
}

void Octopusses::advance() {
    for (int i = 0; i < energyLevels.size(); i++) {
        for (int j = 0; j < energyLevels[i].size(); j++) {
            this->energyLevels[i][j]++;
        }
    }

    bool flag = true;
    while (flag) {
        flag = false;
        for (int i = 0; i < energyLevels.size(); i++) {
            for (int j = 0; j < energyLevels[i].size(); j++) {
                if (this->energyLevels[i][j] > 9) {
                    this->energyLevels[i][j] = -1;
                    this->flashes++;
                    flag = true;

                    Point point(j, i);
                    vector<Point> neighbors = this->findNeighbors(point);
                    for (Point neighbor : neighbors) {
                        if (this->energyLevels[neighbor.y][neighbor.x] > -1) {
                            this->energyLevels[neighbor.y][neighbor.x]++;
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < energyLevels.size(); i++) {
        for (int j = 0; j < energyLevels[i].size(); j++) {
            if (this->energyLevels[i][j] == -1) {
                this->energyLevels[i][j] = 0;
            }
        }
    }

    this->steps++;
    this->output();
}

void Octopusses::advance(int steps) {
    for (int i = 0; i < steps; i++) {
        this->advance();
    }
}

void Octopusses::advanceUntilSync() {
    int size = this->energyLevels.size() * this->energyLevels[0].size();
    int tmp = this->flashes;
    while (this->flashes != tmp + size) {
        tmp = this->flashes;
        this->advance();
    }
    cout << endl << "All octopusses flashed for the first time after " << this->steps << " steps." << endl;
}

void Octopusses::output() {
    BMP image;
    image.SetSize(this->energyLevels[0].size(), this->energyLevels.size());
    image.SetBitDepth(32);

    for (int i = 0; i < this->energyLevels.size(); i++) {
        for (int j = 0; j < this->energyLevels[i].size(); j++) {
            int val = this->energyLevels[i][j] * 255 / 9;
            draw(image, j, i, val, val, val);
        }
    }
    string filename = "bin/energyLevels" + to_string(this->steps) + ".bmp";
    image.WriteToFile(filename.c_str());

    for (int i = 0; i < this->energyLevels.size(); i++) {
        for (int j = 0; j < this->energyLevels[i].size(); j++) {
            if (this->energyLevels[i][j] == 0) {
                draw(image, j, i);
            } else {
                draw(image, j, i, 255, 255, 255);
            }
        }
    }
    filename = "bin/flashes" + to_string(this->steps) + ".bmp";
    image.WriteToFile(filename.c_str());

    cout << "There are a total of " << this->flashes << " total flashes after " << this->steps << " steps." << endl;
}

vector<Point> Octopusses::findNeighbors(Point& point) {
    vector<Point> output;
    bool hasLeft = point.x > 0;
    bool hasRight = point.x < this->energyLevels[point.y].size() - 1;
    bool hasUpper = point.y > 0;
    bool hasLower = point.y < this->energyLevels.size() - 1;

    // Left Neighbor
    if (hasLeft) {
        output.push_back(Point(point.x - 1, point.y));

        if (hasUpper) {
            output.push_back(Point(point.x - 1, point.y - 1));
        }

        if (hasLower) {
            output.push_back(Point(point.x - 1, point.y + 1));
        }
    }

    // Right Neighbor
    if (hasRight) {
        output.push_back(Point(point.x + 1, point.y));

        if (hasUpper) {
            output.push_back(Point(point.x + 1, point.y - 1));
        }

        if (hasLower) {
            output.push_back(Point(point.x + 1, point.y + 1));
        }
    }

    // Upper Neighbor
    if (hasUpper) {
        output.push_back(Point(point.x, point.y - 1));
    }

    // Lower Neighbor
    if (hasLower) {
        output.push_back(Point(point.x, point.y + 1));
    }

    return output;
}

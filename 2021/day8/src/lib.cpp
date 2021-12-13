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
    copy(rhs.begin(), --rhs.end(), ostream_iterator<T>(lhs, ", "));
    if (rhs.size() - 1 >= 0) {
        cout << rhs[rhs.size() - 1];
    }
    lhs << "]";
    return lhs;
}

template<class T> vector<T> operator-(vector<T>& lhs, vector<T>& rhs) {
    vector<T> output((lhs.size() > rhs.size()) ? lhs.size() : rhs.size());
    typename  vector<T>::iterator it = set_difference(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), output.begin());
    output.resize(it - output.begin());
    return output;
}

string operator-(string& lhs, string& rhs) {
    vector<char> first(lhs.begin(), lhs.end());
    vector<char> second(rhs.begin(), rhs.end());
    vector<char> result = first - second;
    string output(result.begin(), result.end());
    return output;
}

void draw(BMP& image, int i, int j, int r, int g, int b, int a) {
    image(i, j)->Red = r;
    image(i, j)->Green = g;
    image(i, j)->Blue = b;
    image(i, j)->Alpha = a;
}

void drawDisplay(char num, BMP& image, int i, int j, int r, int g, int b, int a) {
    vector<bool> segments = highlightSegments(num);

    if (segments[0]) {
        for (int l = 1; l < 5; l++) {
            draw(image, i*7 + l, j*12);
        }
    }

    if (segments[1]) {
        for (int k = 1; k < 5; k++) {
            draw(image, i*7 + 5, j*12 + k);
        }
    }

    if (segments[2]) {
        for (int k = 6; k < 10; k++) {
            draw(image, i*7 + 5, j*12 + k);
        }
    }

    if (segments[3]) {
        for (int l = 1; l < 5; l++) {
            draw(image, i*7 + l, j*12 + 10);
        }
    }

    if (segments[4]) {
        for (int k = 6; k < 10; k++) {
            draw(image, i*7, j*12 + k);
        }
    }

    if (segments[5]) {
        for (int k = 1; k < 5; k++) {
            draw(image, i*7, j*12 + k);
        }
    }

    if (segments[6]) {
        for (int l = 1; l < 5; l++) {
            draw(image, i*7 + l, j*12 + 5);
        }
    }
}

vector<bool> highlightSegments(char num) {
    vector<bool> segments(7, false);
    switch (num) {
    case '0':
        segments[0] = true;
        segments[1] = true;
        segments[2] = true;
        segments[3] = true;
        segments[4] = true;
        segments[5] = true;
        break;
    
    case '1':
        segments[1] = true;
        segments[2] = true;
        break;
    
    case '2':
        segments[0] = true;
        segments[1] = true;
        segments[3] = true;
        segments[4] = true;
        segments[6] = true;
        break;
    
    case '3':
        segments[0] = true;
        segments[1] = true;
        segments[2] = true;
        segments[3] = true;
        segments[6] = true;
        break;
    
    case '4':
        segments[1] = true;
        segments[2] = true;
        segments[5] = true;
        segments[6] = true;
        break;
    
    case '5':
        segments[0] = true;
        segments[2] = true;
        segments[3] = true;
        segments[5] = true;
        segments[6] = true;
        break;
    
    case '6':
        segments[0] = true;
        segments[2] = true;
        segments[3] = true;
        segments[4] = true;
        segments[5] = true;
        segments[6] = true;
        break;
    
    case '7':
        segments[0] = true;
        segments[1] = true;
        segments[2] = true;
        break;
    
    case '8':
        segments[0] = true;
        segments[1] = true;
        segments[2] = true;
        segments[3] = true;
        segments[4] = true;
        segments[5] = true;
        segments[6] = true;
        break;
    
    case '9':
        segments[0] = true;
        segments[1] = true;
        segments[2] = true;
        segments[3] = true;
        segments[5] = true;
        segments[6] = true;
        break;
    
    default:
        break;
    }
    return segments;
}

Displays::Displays(string entry) {
    vector<string> tmp = parse(entry, " | ");
    this->patterns = parse(tmp[0], " ");
    this->outputs = parse(tmp[1], " ");

    this->basicDigitsCount = 0;
    for (string output : this->outputs) {
        int outputSize = output.size();
        // Check if output size matches the number of segments required to light up 1, 4, 7, or 8.
        if (outputSize == 2 || outputSize == 4 || outputSize == 3 || outputSize == 7) {
            this->basicDigitsCount++;
        }
    }

    for (string pattern : this->patterns) {
        sort(pattern.begin(), pattern.end());
        int patternSize = pattern.size();
        // Check if output size matches the number of segments required to light up 1, 4, 7, or 8.
        switch (patternSize) {
        case 2:
            this->one = pattern;
            break;
        case 4:
            this->four = pattern;
            break;
        case 3:
            this->seven = pattern;
            break;
        case 7:
            this->eight = pattern;
            break;
        case 5:
            this->twoThreeFive.push_back(pattern);
            break;
        case 6:
        default:
            this->zeroSixNine.push_back(pattern);
            break;
        }
    }

    this->output = this->decode();
}

string Displays::decode() {
    this->a = (this->seven - this->one)[0];

    for (string num : this->zeroSixNine) {
        string tmp = this->one - num;
        if (!tmp.empty()) {
            this->b = tmp[0];
            this->c = (this->one - tmp)[0];
            this->six = num;
            break;
        }
    }

    for (string num : this->zeroSixNine) {
        string fg = this->four - this->one;
        string tmp = fg - num;
        if (!tmp.empty()) {
            this->g = tmp[0];
            this->f = (fg - tmp)[0];
            this->zero = num;
            break;
        }
    }

    for (string num : this->zeroSixNine) {
        string tmp = this->eight - this->four;
        string de = tmp - this->seven;
        tmp = de - num;
        if (!tmp.empty()) {
            this->e = tmp[0];
            this->d = (de - tmp)[0];
            this->nine = num;
            break;
        }
    }

    for (string num : this->twoThreeFive) {
        if ((num - this->one).size() == 3) {
            this->three = num;
        } else if ((num - this->nine).size() == 1) {
            this->two = num;
        } else {
            this->five = num;
        }
    }

    string output;
    for (string tmp : this->outputs) {
        sort(tmp.begin(), tmp.end());
        switch (tmp.size()) {
        case 2:
            output += '1';
            break;
        case 4:
            output += '4';
            break;
        case 3:
            output += '7';
            break;
        case 7:
            output += '8';
            break;
        default:
            if ((tmp - this->zero).empty()) {
                output += '0';
            } else if ((tmp - this->two).empty()) {
                output += '2';
            } else if ((tmp - this->three).empty()) {
                output += '3';
            } else if ((tmp - this->five).empty()) {
                output += '5';
            } else if ((tmp - this->six).empty()) {
                output += '6';
            } else {
                output += '9';
            }
            break;
        }
    }
    return output;
}

void Displays::toConsole() {
    cout << "Patterns: " << this->patterns << endl;
    cout << "Outputs: " << this->outputs << endl;
    cout << "The pattern for the digit '0' is " << this->zero << endl;
    cout << "The pattern for the digit '1' is " << this->one << endl;
    cout << "The pattern for the digit '2' is " << this->two << endl;
    cout << "The pattern for the digit '3' is " << this->three << endl;
    cout << "The pattern for the digit '4' is " << this->four << endl;
    cout << "The pattern for the digit '5' is " << this->five << endl;
    cout << "The pattern for the digit '6' is " << this->six << endl;
    cout << "The pattern for the digit '7' is " << this->seven << endl;
    cout << "The pattern for the digit '8' is " << this->eight << endl;
    cout << "The pattern for the digit '9' is " << this->nine << endl;

    cout << " " << string(4, this->a) << " " << endl;
    cout << this->f << "    " << this->b << endl;
    cout << this->f << "    " << this->b << endl;
    cout << " " << string(4, this->g) << " " << endl;
    cout << this->e << "    " << this->c << endl;
    cout << this->e << "    " << this->c << endl;
    cout << " " << string(4, this->d) << " " << endl;

    cout << "In the output values, digits 1, 4, 7, and 8 appear " << this->basicDigitsCount << " times." << endl;
    cout << "The output value is " << this->output << endl;
    cout << endl;
}

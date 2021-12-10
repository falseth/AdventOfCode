#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

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

    int x_pos = 0, depth = 0, aim = 0;
    for (int i = 0; i < input.size(); i++) {
        switch (input[i][0]) {
        case 'u':
            aim -= stoi(input[i].substr(input[i].find(' ') + 1, input[i].size()));
            break;

        case 'd':
            aim += stoi(input[i].substr(input[i].find(' ') + 1, input[i].size()));
            break;

        case 'f':
            x_pos += stoi(input[i].substr(input[i].find(' ') + 1, input[i].size()));
            depth += stoi(input[i].substr(input[i].find(' ') + 1, input[i].size())) * aim;
            break;

        default:
            break;
        }
    }

    cout << "The resulting horizontal position is " << x_pos << "." << endl;
    cout << "The resulting depth is " << depth << "." << endl;
    cout << "The product of both of them is " << x_pos * depth << "." << endl;
    return 0;
}
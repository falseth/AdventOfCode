#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

int main(void) {
    ifstream file;
    file.open("2021/day3/input.txt");

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

    int gamma = 0, epsilon = 0;
    int zero_count = 0, one_count = 0;
    int num_size = input[0].size();

    for (int i = 0; i < num_size; i++) {
        for (int j = 0; j < input.size(); j++) {
            if (input[j][i] == '1') {
                one_count++;
            } else {
                zero_count++;
            }
        }

        if (one_count > zero_count) {
            gamma += pow(2, num_size - i - 1);
        }

        zero_count = 0;
        one_count = 0;
    }

    epsilon = pow(2, num_size) - gamma - 1;

    cout << "The gamma rate is " << gamma << "." << endl;
    cout << "The epsilon rate is " << epsilon << "." << endl;
    cout << "The power consumption of the submarine is " << gamma * epsilon << "." << endl;
    return 0;
}
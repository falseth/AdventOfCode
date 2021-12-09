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

    // Part 1
    int gamma = 0, epsilon = 0;
    int zero_count, one_count;
    int num_size = input[0].size();

    for (int i = 0; i < num_size; i++) {
        zero_count = 0;
        one_count = 0;

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
    }

    epsilon = pow(2, num_size) - gamma - 1;

    cout << "The gamma rate is " << gamma << "." << endl;
    cout << "The epsilon rate is " << epsilon << "." << endl;
    cout << "The power consumption of the submarine is " << gamma * epsilon << "." << endl;

    cout << endl;

    // Part 2
    vector<string> O2, CO2;
    for (int j = 0; j < input.size(); j++) {
        O2.push_back(input[j]);
        CO2.push_back(input[j]);
    }

    // Oxygen Generator Rating
    for (int i = 0; i < num_size; i++) {
        zero_count = 0;
        one_count = 0;

        for (int j = 0; j < O2.size(); j++) {
            if (O2[j][i] == '1') {
                one_count++;
            } else {
                zero_count++;
            }
        }

        if (one_count < zero_count) {
            for (int j = 0; j < O2.size(); j++) {
                if (O2[j][i] == '1') {
                    O2.erase(O2.begin() + j);
                    j--;
                }
            }
        } else {
            for (int j = 0; j < O2.size(); j++) {
                if (O2[j][i] == '0') {
                    O2.erase(O2.begin() + j);
                    j--;
                }
            }
        }

        if (O2.size() <= 1) {
            break;
        }
    }

    // CO2 Scrubber Rating
    for (int i = 0; i < num_size; i++) {
        zero_count = 0;
        one_count = 0;

        for (int j = 0; j < CO2.size(); j++) {
            if (CO2[j][i] == '1') {
                one_count++;
            } else {
                zero_count++;
            }
        }

        if (one_count < zero_count) {
            for (int j = 0; j < CO2.size(); j++) {
                if (CO2[j][i] == '0') {
                    CO2.erase(CO2.begin() + j);
                    j--;
                }
            }
        } else {
            for (int j = 0; j < CO2.size(); j++) {
                if (CO2[j][i] == '1') {
                    CO2.erase(CO2.begin() + j);
                    j--;
                }
            }
        }

        if (CO2.size() <= 1) {
            break;
        }
    }

    cout << "The oxygen generator rating is " << stoi(O2[0], nullptr, 2) << "." << endl;
    cout << "The CO2 scrubber rating is " << stoi(CO2[0], nullptr, 2) << "." << endl;
    cout << "The life support rating of the submarine is " << stoi(O2[0], nullptr, 2) * stoi(CO2[0], nullptr, 2) << "." << endl;
    return 0;
}
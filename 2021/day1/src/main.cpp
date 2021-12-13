#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main(void) {
    int window_size;
    cout << "Window Size: ";
    cin >> window_size;

    ifstream file;
    file.open("src/input.txt");

    if (!file.is_open()) {
        cout << "AN ERROR HAS OCCURRED" << endl;
        return 1;
    }

    string line;
    vector<int> input;
    while (getline(file, line)) {
        input.push_back(stoi(line));
    }
    file.close();

    int increasing_times = 0;
    int last_depth = 0, current_depth = 0;

    for (int j = 0; j < window_size; j++) {
        last_depth += input[j];
    }

    for (int i = 1; i < input.size() - window_size + 1; i++) {
        for (int j = 0; j < window_size; j++) {
            current_depth += input[i+j];
        }

        if (current_depth > last_depth) {
            increasing_times++;
        }

        last_depth = current_depth;
        current_depth = 0;
    }

    cout << "With a window size of " << window_size << ", the depth increases " << increasing_times << " number of times." << endl;
    return 0;
}
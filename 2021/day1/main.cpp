#include <iostream>
#include <fstream>

using namespace std;

int main(void) {
    ifstream file;
    file.open("2021/day1/input.txt");

    if (!file.is_open()) {
        cout << "AN ERROR HAS OCCURRED" << endl;
        return 1;
    }

    string line;
    int increasing_times = 0;
    int last_depth, current_depth;

    getline(file, line);
    last_depth = stoi(line);

    while (getline(file, line)) {
        current_depth = stoi(line);
        
        if (current_depth > last_depth) {
            increasing_times++;
        }

        last_depth = current_depth;
    }

    cout << increasing_times << endl;
    file.close();
    return 0;
}
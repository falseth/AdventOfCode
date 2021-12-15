#include "lib.hpp"

using namespace std;

int main(void) {
    ifstream file;
    file.open("src/input.txt");

    if (!file.is_open()) {
        cout << "ERROR OPENING INPUT FILE" << endl;
        return 1;
    }

    string line;
    vector<string> input;
    while (getline(file, line)) {
        input.push_back(line);
    }
    file.close();

    NavSystem navSystem(input);
    navSystem.output();

    return 0;
}

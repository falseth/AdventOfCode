#include "lib.hpp"

using namespace std;

int main(void) {
    ifstream file;
    file.open("src/test.txt");

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

    Map map(input);
    cout << input;
    return 0;
}
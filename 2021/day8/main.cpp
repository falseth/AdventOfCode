#include "lib.hpp"

using namespace std;

int main(void) {
    ifstream file;
    file.open("input.txt");

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

    vector<Displays> displaysArray;
    int totalCount = 0;
    for (string entry : input) {
        Displays displays(entry);
        displays.toConsole();
        totalCount += displays.basicDigitsCount;
        displaysArray.push_back(displays);
    }
    cout << "The total amount of time digits 1, 4, 7, and 8 appear on the output is " << totalCount << " times." << endl;
    return 0;
}

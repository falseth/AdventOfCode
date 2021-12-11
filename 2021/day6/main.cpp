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

    int daysToAdvance;
    cout << "Days to Advance: ";
    cin >> daysToAdvance;

    Lanternfishes lanternfishes(parse(input[0], ","), true, false);
    lanternfishes.advance(daysToAdvance);
    lanternfishes.close();
    return 0;
}

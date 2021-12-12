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
    int totalBasicDigitsCount = 0;
    int outputSum = 0;
    for (string entry : input) {
        Displays displays(entry);
        displays.toConsole();
        totalBasicDigitsCount += displays.basicDigitsCount;
        outputSum += stoi(displays.output);
        displaysArray.push_back(displays);
    }

    BMP image;
    image.SetSize(displaysArray[0].output.size() * 7 - 1, displaysArray.size() * 12 - 1);
    image.SetBitDepth(32);
    for (int i = 0; i < displaysArray.size(); i++) {
        for (int j = 0; j < displaysArray[i].output.size(); j++) {
            drawDisplay(displaysArray[i].output[j], image, j, i);
        }
    }
    image.WriteToFile("output.bmp");

    cout << endl;
    cout << "The total amount of time digits 1, 4, 7, and 8 appear on the output is " << totalBasicDigitsCount << " times." << endl;
    cout << "The output value is " << outputSum << endl;
    return 0;
}

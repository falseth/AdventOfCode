#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<string> parse(string input, string delimiter);

class Lanternfishes {
public:
    vector<int> lanternfishes;
    ofstream file;
    int daysElapsed;

    Lanternfishes(vector<string> lanternfishes) {
        this->daysElapsed = 0;

        for (string lanternfish : lanternfishes) {
            this->lanternfishes.push_back(stoi(lanternfish));
        }

        this->file.open("output.txt");
        if (!this->file.is_open()) {
            cout << "ERROR OPENING OUTPUT FILE" << endl;
            return;
        }

        this->file << "Initial State: " << this->toString() << endl;
    }

    void advance() {
        int newFishes = 0;
        for (int& lanternfish : this->lanternfishes) {
            if (lanternfish == 0) {
                lanternfish = 6;
                newFishes++;
            } else {
                lanternfish--;
            }
        }

        for (int i = 0; i < newFishes; i++) {
            this->lanternfishes.push_back(8);
        }

        this->daysElapsed++;
        this->file << "After ";
        if (this->daysElapsed < 10) {
            this->file << " ";
        }
        this->file << this->daysElapsed << " days: " << this->toString() << endl;
    }

    void advance(int days) {
        for (int i = 0; i < days; i++) {
            this->advance();
        }
    }

    string toString() {
        string output = to_string(this->lanternfishes[0]);
        for (int i = 1; i < this->lanternfishes.size(); i++) {
            output += ",";
            output += to_string(this->lanternfishes[i]);
        }
        return output;
    }

    int size() {
        return this->lanternfishes.size();
    }

    void close() {
        this->file << endl << "There are " << this->size() << " lanternfishes after " << this->daysElapsed << " days." << endl;
        this->file.close();

        cout << "There are " << this->size() << " lanternfishes after " << this->daysElapsed << " days." << endl;
    }
};

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

    Lanternfishes lanternfishes(parse(input[0], ","));
    lanternfishes.advance(daysToAdvance);
    lanternfishes.close();
    return 0;
}

vector<string> parse(string input, string delimiter) {
    size_t pos = 0;
    string token;
    vector<string> output;

    while ((pos = input.find(delimiter)) == 0) {
        input.erase(0, delimiter.length());
    }

    while ((pos = input.find(delimiter)) != string::npos) {
        token = input.substr(0, pos);
        output.push_back(token);
        input.erase(0, pos + delimiter.length());

        while ((pos = input.find(delimiter)) == 0) {
            input.erase(0, delimiter.length());
        }
    }
    output.push_back(input);

    return output;
}
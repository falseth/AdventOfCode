#include "lib.hpp"

using namespace std;

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

Crabs::Crabs(vector<string>& positions) {
    int min = stoi(positions[0]), max = stoi(positions[0]);

    for (string position : positions) {
        this->positions.push_back(stoi(position));

        if (stoi(position) < min) {
            min = stoi(position);
        } else if (stoi(position) > max) {
            max = stoi(position);
        }
    }

    this->min = min;
    this->max = max;

    this->crabsCount = vector<int>(max - min + 1, 0);
    for (int position : this->positions) {
        this->crabsCount[position - min]++;
    }

    int lowest = 0;
    for (int j = 0; j < crabsCount.size(); j++) {
        lowest += j * crabsCount[j];
    }

    for (int i = 1; i < crabsCount.size(); i++) {
        int tmp = 0;
        for (int j = 0; j < crabsCount.size(); j++) {
            tmp += abs(i - j) * crabsCount[j];
        }

        if (tmp >= lowest) {
            this->lowestPosition = i - 1 + this->min;
            this->lowestScore = lowest;
            break;
        } else {
            lowest = tmp;
        }
    }
}

void Crabs::toConsole() {
    cout << "The horizontal position that the crabs";
    cout << " can align to using the least fuel possible";
    cout << " is " << this->lowestPosition;
    cout << " where " << this->lowestScore;
    cout << " units of fuel must be spent.";
}

#include "lib.hpp"

using namespace std;

// https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
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

// https://stackoverflow.com/questions/33665257/how-to-overload-ostream-for-vector-to-print-all-collection-from-vector
template<class T> ostream& operator<<(ostream& lhs, vector<T>& rhs) {
    lhs << "[";
    copy(rhs.begin(), --rhs.end(), ostream_iterator<T>(lhs, ", "));
    if (rhs.size() - 1 >= 0) {
        cout << rhs[rhs.size() - 1];
    }
    lhs << "]";
    return lhs;
}

Displays::Displays(string entry) {
    vector<string> tmp = parse(entry, " | ");
    this->patterns = parse(tmp[0], " ");
    this->outputs = parse(tmp[1], " ");

    this->basicDigitsCount = 0;
    for (string output : outputs) {
        int outputSize = output.size();
        // Check if output size matches the number of segments required to light up 1, 4, 7, or 8.
        if (outputSize == 2 || outputSize == 4 || outputSize == 3 || outputSize == 7) {
            this->basicDigitsCount++;
        }
    }
}

void Displays::toConsole() {
    cout << "Patterns: " << this->patterns << endl;
    cout << "Outputs: " << this->outputs << endl;
    cout << "In the output values, digits 1, 4, 7, and 8 appear " << this->basicDigitsCount << " times." << endl;
    cout << endl;
}

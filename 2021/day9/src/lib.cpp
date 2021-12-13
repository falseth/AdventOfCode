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
template<typename T> ostream& operator<<(ostream& lhs, vector<T>& rhs) {
    lhs << "[";
    for (int i = 0; i < rhs.size() - 1; i++) {
        cout << rhs[i] << ", ";
    }

    if (rhs.size() - 1 >= 0) {
        cout << rhs[rhs.size() - 1];
    }
    lhs << "]";
    return lhs;
}

Map::Map(vector<string> heightMap) {
    int rows = heightMap.size();
    int cols = heightMap[0].size();

    this->heightMap = vector<vector<int>>(rows, vector<int>(cols));
    for (int i = 0; i < heightMap.size(); i++) {
        for (int j = 0; j < heightMap[i].size(); j++) {
            this->heightMap[i][j] = heightMap[i][j];
        }
    }
}

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
    for (int i = 0; i < rhs.size() - 1; i++) {
        cout << rhs[i] << ", ";
    }

    if (rhs.size() - 1 >= 0) {
        cout << rhs[rhs.size() - 1];
    }
    lhs << "]";
    return lhs;
}

ostream& operator<<(ostream& lhs, vector<int> rhs) {
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

vector<int> max(vector<int>& nums, int n) {
    vector<int> output(n, 0);

    for (int num : nums) {
        for (int i = 0; i < n; i++) {
            if (output[i] < num) {
                output.insert(output.begin()+i, num);
                output.pop_back();
                break;
            }
        }
    }

    return output;
}

vector<Int> max(vector<Int>& nums, int n) {
    vector<Int> output(n, Int(0));

    for (Int num : nums) {
        for (long i = 0; i < n; i++) {
            if (uCmp(output[i], num) < 0) {
                output.insert(output.begin()+i, num);
                output.pop_back();
                break;
            }
        }
    }

    return output;
}

Int::Int() {
    Int(0);
}

Int::Int(int num) {
    if (num >= 0) {
        this->sign = 0;
        this->num = to_string(num);
        this->size = this->num.size();
    }
    else {
        this->sign = 1;
        this->num = to_string(num).substr(1, string::npos);
        this->size = this->num.size();
    }
}

void Int::operator++(int) {
    Int num(1);
    this->operator+=(num);
}

void Int::operator+=(Int& rhs) {
    if (this->sign != rhs.sign) {
        Int tmp(rhs);
        tmp.sign = !tmp.sign;
        this->operator-=(tmp);
    }

    Int& big = (this->size > rhs.size) ? (*this) : rhs;
    Int& small = (this->size > rhs.size) ? rhs : (*this);

    long tmp, carry = 0;
    string num(big.size + 2, '0');

    for (long i = 0; i < small.size; i++) {
        tmp = big.num[big.size - i - 1] + small.num[small.size - i - 1] + carry - 2 * '0';
        carry = tmp / 10;
        num[big.size - i] = tmp % 10 + '0';
    }

    for (long i = small.size; i < big.size; i++) {
        tmp = big.num[big.size - i - 1] + carry - '0';
        carry = tmp / 10;
        num[big.size - i] = tmp % 10 + '0';
    }

    num[big.size + 1] = '\0';
    if (carry == 0) {
        for (long i = 0; i < big.size + 1; i++) {
            num[i] = num[i + 1];
        }
        num.pop_back();
    }
    else {
        num[0] = '1';
    }

    this->num = num;
    this->size = big.size + carry;
    if (this->num[0] == '0') {
        this->sign = 0;
    }
}

void Int::operator-=(Int& rhs) {
    if (this->sign != rhs.sign) {
        Int tmp(rhs);
        tmp.sign = !tmp.sign;
        this->operator+=(tmp);
    }

    Int& big = (this->size > rhs.size) ? (*this) : rhs;
    Int& small = (this->size > rhs.size) ? rhs : (*this);

    bool sign;
    if (uCmp(*this, rhs) > 0) {
        sign = this->sign;
    }
    else {
        sign = !rhs.sign;
    }

    long tmp, borrow = 0;
    string num(big.size + 1, '0');

    for (long i = 0; i < small.size; i++) {
        tmp = 10 + big.num[big.size - i - 1] - small.num[small.size - i - 1] - borrow;
        borrow = !(tmp / 10);
        num[big.size - i - 1] = tmp % 10 + '0';
    }

    for (long i = small.size; i < big.size; i++) {
        tmp = 10 + big.num[big.size - i - 1] - borrow - '0';
        borrow = !(tmp / 10);
        num[big.size - i - 1] = tmp % 10 + '0';
    }

    num[big.size] = '\0';
    for (tmp = 0; tmp < big.size - 1; tmp++) {
        if (num[tmp] != '0') {
            break;
        }
    }

    for (long i = tmp; i <= big.size; i++) {
        num[i - tmp] = num[i];
    }

    num.resize(big.size + 1 - tmp);

    this->num = num;
    this->size = big.size - tmp;
    if (this->num[0] == '0') {
        this->sign = 0;
    }
    else {
        this->sign = sign;
    }
}

void Int::operator*=(Int& rhs) {
    if (this->num[0] == '0' || rhs.num[0] == '0') {
        this->num = "0";
        this->size = 1;
        this->sign = false;
        return;
    }

    Int result = Int(0);
    for (long i = 0; i < rhs.size; i++) {
        Int tmp = Int(0);
        for (long j = 0; j < rhs.num[rhs.size - i - 1] - '0'; j++) {
            tmp += (*this);
        }

        tmp.num.resize(tmp.size + i + 1);
        for (long j = tmp.size; j < tmp.size + i; j++) {
            tmp.num[j] = '0';
        }
        tmp.num[tmp.size + i] = '\0';
        tmp.size += i;

        result += tmp;
    }

    this->num = result.num;
    this->size = result.size;
    this->sign = (this->sign == rhs.sign) ? false : true;
}

int uCmp(Int& lhs, Int& rhs) {
    // Test size
    if (lhs.size > rhs.size) {
        return 1;
    }
    else if (lhs.size < rhs.size) {
        return -1;
    }
    else {
        // Test the first digit difference
        long i;
        for (i = 0; i < lhs.size; i++) {
            if (lhs.num[i] != rhs.num[i]) {
                break;
            }
        }

        if (i == lhs.size) {
            return 0;
        }
        else if (lhs.num[i] > rhs.num[i]) {
            return 1;
        }
        else {
            return -1;
        }
    }
}

bool operator<(Int& lhs, Int& rhs) {
    // Test signs
    if (lhs.sign == 0 && rhs.sign == 1) {
        return false;
    }
    else if (lhs.sign == 1 && rhs.sign == 0) {
        return true;
    }

    // Test size (assuming positive)
    bool tmp = uCmp(lhs, rhs);

    // Flip the sign if lhs and rhs are negative
    if (lhs.sign == 0) {
        return tmp;
    } else {
        return -tmp;
    }
}

ostream& operator<<(ostream& lhs, Int& rhs) {
    if (rhs.sign == 1) {
        lhs << "-";
    }
    lhs << rhs.num;
    return lhs;
}

NavSystem::NavSystem(vector<string>& lines) : lines(lines) {
    this->computeScores();
}

Int NavSystem::computeCorrupted(string& line) {
    vector<char> stack;
    for (char chr : line) {
        if (chr == '(' || chr == '[' || chr == '{' || chr == '<') {
            stack.push_back(chr);
            continue;
        }

        if (chr == ')' && stack.back() != '(') {
            return Int(3);
        } else if (chr == ']' && stack.back() != '[') {
            return Int(57);
        } else if (chr == '}' && stack.back() != '{') {
            return Int(1197);
        } else if (chr == '>' && stack.back() != '<') {
            return Int(25137);
        } else {
            stack.pop_back();
        }
    }
    return Int(0);
}

Int NavSystem::computeIncomplete(string& line) {
    vector<char> stack;
    for (char chr : line) {
        if (chr == '(' || chr == '[' || chr == '{' || chr == '<') {
            stack.push_back(chr);
            continue;
        }

        if (chr == ')' && stack.back() != '(' || chr == ']' && stack.back() != '[' || chr == '}' && stack.back() != '{' || chr == '>' && stack.back() != '<') {
            return Int(0);
        } else {
            stack.pop_back();
        }
    }

    Int tmp(0);
    while (!stack.empty()) {
        char chr = stack.back();
        stack.pop_back();
        
        Int mul(5);
        tmp *= mul;

        Int add;
        switch (chr) {
        case '(':
            add = Int(1);
            break;
        case '[':
            add = Int(2);
            break;
        case '{':
            add = Int(3);
            break;
        case '<':
            add = Int(4);
            break;
        default:
            break;
        }
        tmp += add;
    }
    return tmp;
}

void NavSystem::computeScores() {
    this->corruptedScore = 0;
    for (string line : this->lines) {
        Int tmp = this->computeCorrupted(line);
        this->corruptedScore += tmp;
    }

    vector<Int> tmp;
    for (string line : this->lines) {
        Int score = this->computeIncomplete(line);
        if (score.num[0] != '0') {
            tmp.push_back(score);
        }
    }
    this->incompleteScore = max(tmp, tmp.size())[(tmp.size() - 1) / 2];
}

void NavSystem::output() {
    cout << "The total syntax error score for the corrupted lines are " << this->corruptedScore << "." << endl;
    cout << "The middle score for the incomplete lines are " << this->incompleteScore << "." << endl;
}

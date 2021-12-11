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

Lanternfishes::Lanternfishes(vector<string> lanternfishes, bool fastMode = true, bool doesOutput = false) {
    this->daysElapsed = 0;
    this->fastMode = fastMode;
    this->doesOutput = doesOutput;

    for (string lanternfish : lanternfishes) {
        this->lanternfishes.push_back(stoi(lanternfish));
    }

    if (this->fastMode) {
        this->quickCount = vector<Int>(9, Int(0));
        for (int lanternfish : this->lanternfishes) {
            this->quickCount[lanternfish]++;
        }
    } else {
        this->file.open("output.txt");
        if (!this->file.is_open()) {
            cout << "ERROR OPENING OUTPUT FILE" << endl;
            return;
        }
        this->file << "Initial State: " << this->toString() << endl;
    }
}

void Lanternfishes::advance() {
    if (this->fastMode) {
        Int zeros = this->quickCount[0];
        for (int i = 0; i < 8; i++) {
            this->quickCount[i] = this->quickCount[i+1];
        }
        this->quickCount[6] += zeros;
        this->quickCount[8] = zeros;
    } else {
        long newFishes = 0;
        for (int& lanternfish : this->lanternfishes) {
            if (lanternfish == 0) {
                lanternfish = 6;
                newFishes++;
            } else {
                lanternfish--;
            }
        }

        for (long i = 0; i < newFishes; i++) {
            this->lanternfishes.push_back(8);
        }
    }

    this->daysElapsed++;
    if (this->doesOutput) {
        output();
    }

    cout << "Day " << this->daysElapsed << " Elapsed." << endl;
}

void Lanternfishes::advance(int days) {
    for (int i = 0; i < days; i++) {
        this->advance();
    }
}

void Lanternfishes::output() {
    this->file << "After ";
    if (this->daysElapsed < 10) {
        this->file << " ";
    }
    this->file << this->daysElapsed << " days: " << this->toString() << endl;
}

string Lanternfishes::toString() {
    string output;

    if (fastMode) {
        for (int i = 0; i <= 8; i++) {
            for (Int j = 0; j < this->quickCount[i]; j++) {
                output += to_string(i);
                output += ",";
            }
        }
    } else {
        for (int i = 1; i < this->lanternfishes.size(); i++) {
            output += to_string(this->lanternfishes[i]);
            output += ",";
        }
    }

    output.pop_back();
    return output;
}

Int Lanternfishes::size() {
    if (fastMode) {
        Int sum = 0;
        for (int i = 0; i <= 8; i++) {
            sum += this->quickCount[i];
        }
        return sum;
    } else {
        return this->lanternfishes.size();
    }
}

void Lanternfishes::close() {
    Int fishCount = this->size();

    if (!fastMode) {
        this->file << endl << "There are " << fishCount << " lanternfishes after " << this->daysElapsed << " days." << endl;
        this->file.close();
    }
    cout << "There are " << fishCount << " lanternfishes after " << this->daysElapsed << " days." << endl;
}

Int::Int() {
    Int(0);
}

Int::Int(int num) {
    if (num >= 0) {
        this->sign = 0;
        this->num = to_string(num);
        this->size = this->num.size();
    } else {
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
    } else {
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
    } else {
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
    } else {
        this->sign = sign;
    }
}

int uCmp(Int& lhs, Int& rhs) {
    // Test size
    if (lhs.size > rhs.size) {
        return 1;
    } else if (lhs.size < rhs.size) {
        return -1;
    } else {
        // Test the first digit difference
        long i;
        for (i = 0; i < lhs.size; i++) {
            if (lhs.num[i] != rhs.num[i]) {
                break;
            }
        }
        
        if (i == lhs.size) {
            return 0;
        } else if (lhs.num[i] > rhs.num[i]) {
            return 1;
        } else {
            return -1;
        }
    }
}

bool operator<(Int& lhs, Int& rhs) {
    // Test signs
    if (lhs.sign == 0 && rhs.sign == 1) {
        return false;
    } else if (lhs.sign == 1 && rhs.sign == 0) {
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

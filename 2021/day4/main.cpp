#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>

using namespace std;

class Bingo {
public:
    vector<vector<int>> board = vector<vector<int>>(5, vector<int>(5, 0));
    vector<vector<int>> marks = vector<vector<int>>(5, vector<int>(5, false));
    bool has_won = false;
    int score = 0;
    int steps_to_win = 0;
    bool is_col_win = false;
    int win_index = 0;

    void draw_num(int num) {
        if (has_won) {
            return;
        }

        steps_to_win++;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (board[i][j] == num) {
                    marks[i][j] = true;
                    check_win();
                    if (has_won) {
                        calculate_score(num);
                    }
                }
            }
        }
    }

    void to_console() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (has_won && is_col_win && j==win_index || has_won && !is_col_win && i==win_index) {
                    SetConsoleTextAttribute(hConsole, 0xFC);
                } else if (marks[i][j] == 1) {
                    SetConsoleTextAttribute(hConsole, 0x0C);
                } else {
                    SetConsoleTextAttribute(hConsole, 0x0F);
                }

                if (board[i][j] < 10) {
                    cout << "0";
                }
                cout << std::to_string(board[i][j]);

                if (has_won && !is_col_win && i==win_index && j!=4) {
                    SetConsoleTextAttribute(hConsole, 0xFC);
                } else {
                    SetConsoleTextAttribute(hConsole, 0x0F);
                }
                cout << " ";
            }
            SetConsoleTextAttribute(hConsole, 0x0F);
            cout << endl;
        }

        SetConsoleTextAttribute(hConsole, 0x0F);
        cout << "Steps to Win: " << steps_to_win << endl;
        cout << "Final Score: " << score << endl;
    }

private:
    void check_win() {
        int row, col;

        // Row Check
        for (row = 0; row < 5; row++) {
            for (col = 0; col < 5; col++) {
                if (marks[row][col] == false) {
                    break;
                }
            }

            if (col == 5) {
                has_won = true;
                is_col_win = false;
                win_index = row;
                return;
            }
        }

        // Column Check
        for (col = 0; col < 5; col++) {
            for (row = 0; row < 5; row++) {
                if (marks[row][col] == false) {
                    break;
                }
            }

            if (row == 5) {
                has_won = true;
                is_col_win = true;
                win_index = col;
                return;
            }
        }
    }

    void calculate_score(int last_num_drawn) {
        int unmarked_sum = 0;
        for (int row = 0; row < 5; row++) {
            for (int col = 0; col < 5; col++) {
                if (marks[row][col] == false) {
                    unmarked_sum += board[row][col];
                }
            }
        }

        score = unmarked_sum * last_num_drawn;
    }
};

vector<string> parse(string input, string delimiter);

int main(void) {
    ifstream file;
    file.open("2021/day4/input.txt");

    if (!file.is_open()) {
        cout << "AN ERROR HAS OCCURRED" << endl;
        return 1;
    }

    string line;
    vector<string> input;
    while (getline(file, line)) {
        input.push_back(line);
    }
    file.close();

    vector<int> drawn_numbers;
    for (string num : parse(input[0], ",")) {
        drawn_numbers.push_back(stoi(num));
    }

    vector<Bingo> bingos;
    for (int i = 2; i < input.size(); i += 6) {
        Bingo bingo;
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                bingo.board[j][k] = stoi(parse(input[i + j], " ")[k]);
            }
        }

        bingos.push_back(bingo);
    }

    for (Bingo& bingo : bingos) {
        for (int num : drawn_numbers) {
            bingo.draw_num(num);
        }
    }

    int least_steps_to_win = bingos[0].steps_to_win;
    for (Bingo bingo : bingos) {
        if (bingo.steps_to_win < least_steps_to_win) {
            least_steps_to_win = bingo.steps_to_win;
        }
    }

    int most_steps_to_win = bingos[0].steps_to_win;
    for (Bingo bingo : bingos) {
        if (bingo.steps_to_win > most_steps_to_win) {
            most_steps_to_win = bingo.steps_to_win;
        }
    }

    for (Bingo bingo : bingos) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if (bingo.steps_to_win == least_steps_to_win) {
            SetConsoleTextAttribute(hConsole, 0x0A);
            cout << "WINNING BOARD" << endl;
        } else if (bingo.steps_to_win == most_steps_to_win) {
            SetConsoleTextAttribute(hConsole, 0x0A);
            cout << "LOSING BOARD" << endl;
        }
        SetConsoleTextAttribute(hConsole, 0x0F);

        bingo.to_console();
        cout << endl;
    }

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
#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool xmas(vector<string>&board, int r, int c, int dr, int dc) {
    string word = "XMAS";
    for(int i = 0; i < 4; i++) {
        if(r < 0 || r >= board.size() || c < 0 || c >= board[0].size())
            return false;
        if(board[r][c] != word[i])
            return false;
        r += dr;
        c += dc;
    }
    return true;
}

int main() {
    vector<string>board;
    string line;
    int total = 0;

    while(getline(cin, line)) {
        board.push_back(line);
    }

    // for each tile on the board {r, c} ...
    for(int r = 0; r < board.size(); r++) {
        for(int c = 0; c < board[0].size(); c++) {
            // ... try to find xmas in each direction {dr, dc}
            for(int dr = -1; dr <= 1; dr++) {
                for(int dc = -1; dc <= 1; dc++) {
                    if(dr == 0 && dc == 0)
                        continue;
                    total += xmas(board, r, c, dr, dc);
                }
            }
        }
    }

    cout << total << endl;
    return 0;
}

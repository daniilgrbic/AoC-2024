#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool xmas(vector<string>&board, int r, int c) {
    if(board[r][c] != 'A')
        return false;
    return (
        board[r-1][c-1]=='M'&&board[r+1][c+1]=='S' ||
        board[r-1][c-1]=='S'&&board[r+1][c+1]=='M'
    ) && (
        board[r+1][c-1]=='M'&&board[r-1][c+1]=='S' ||
        board[r+1][c-1]=='S'&&board[r-1][c+1]=='M'
    );
}

int main() {
    vector<string>board;
    string line;
    int total = 0;

    while(getline(cin, line)) {
        board.push_back(line);
    }

    // for each tile on the board {r, c} check for x-mas originating in it
    for(int r = 1; r+1 < board.size(); r++) {
        for(int c = 1; c+1 < board[0].size(); c++) {
            total += xmas(board, r, c);
        }
    }

    cout << total << endl;
    return 0;
}

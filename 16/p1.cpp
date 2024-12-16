#include <iostream>
#include <cstdint>
#include <vector>
#include <string>
#include <set>

using namespace std;

struct PQItem {
    int cost;
    int direction;
    int row;
    int col;

    bool operator<(const PQItem& other) const {
        if(cost != other.cost)
            return cost < other.cost;
        if(direction != other.direction)
            return direction < other.direction;
        if(row != other.row)
            return row < other.row;
        return col < other.col;
    }
};

int min(int a, int b, int c, int d) {
    return min(min(a, b), min(c, d));
}

void print( vector<vector<vector<int>>> tileCostsDir) {
    for(int i = 0; i < tileCostsDir.size(); i++) {
        for(int j = 0; j < tileCostsDir[0].size(); j++) {
            int cost = min(
                tileCostsDir[i][j][0], tileCostsDir[i][j][1],
                tileCostsDir[i][j][2], tileCostsDir[i][j][3]);
            cout << cost << " ";
        }
        cout << endl;
    }
}

int main() {

    vector<string> maze;
    int startRow, startCol, endRow, endCol;

    string tmpS;
    while(getline(cin, tmpS)) {
        maze.push_back(tmpS);
        size_t f; 
        if((f = tmpS.find('S')) != string::npos) {
            startRow = maze.size() - 1;
            startCol = f;
        }
        if((f = tmpS.find('E')) != string::npos) {
            endRow = maze.size() - 1;
            endCol = f;
        }
    }

    // 0 = ^ , 1 = > , 2 = v , 3 = <
    vector<vector<vector<int>>> tileCostsDir (maze.size(),
        vector<vector<int>>(maze[0].size(), vector<int>(4, INT32_MAX)));
    tileCostsDir[startRow][startCol][0] = 1000;
    tileCostsDir[startRow][startCol][1] =    0;
    tileCostsDir[startRow][startCol][2] = 1000;
    tileCostsDir[startRow][startCol][3] = 1000;

    set<PQItem> pQueue;
    pQueue.insert({1000, 0, startRow, startCol});
    pQueue.insert({   0, 1, startRow, startCol});
    pQueue.insert({1000, 2, startRow, startCol});
    pQueue.insert({1000, 3, startRow, startCol});

    while(!pQueue.empty()) {

        PQItem curr = *pQueue.begin();
        pQueue.erase(pQueue.begin());

        cout << curr.cost << " " << curr.direction << " " << curr.row << " " << curr.col << endl;

        int solution = min(
            tileCostsDir[endRow][endCol][0], tileCostsDir[endRow][endCol][1],
            tileCostsDir[endRow][endCol][2], tileCostsDir[endRow][endCol][3]);
        if(solution <= curr.cost) {
            // print(tileCostsDir);
            cout << solution << endl;
            return 0;
        }

        vector<PQItem> neighbours = {
            {(curr.direction == 0 ? 1 : 1001) + curr.cost, 0, curr.row - 1, curr.col},
            {(curr.direction == 1 ? 1 : 1001) + curr.cost, 1, curr.row, curr.col + 1},
            {(curr.direction == 2 ? 1 : 1001) + curr.cost, 2, curr.row + 1, curr.col},
            {(curr.direction == 3 ? 1 : 1001) + curr.cost, 3, curr.row, curr.col - 1}
        };

        for(PQItem next : neighbours) {
            if(maze[next.row][next.col] == '#'){
                continue;
            }
            if(tileCostsDir[next.row][next.col][next.direction] > next.cost) {
                tileCostsDir[next.row][next.col][next.direction] = next.cost;
                pQueue.insert(next);
            }
        }
    }

    // print(tileCostsDir);
    cout << "Can't reach maze exit!" << endl;
    return 0;
}
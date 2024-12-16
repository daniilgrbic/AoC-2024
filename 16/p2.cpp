#include <iostream>
#include <iomanip>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
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

int min(vector<vector<vector<int>>> tileCostsDir, int row, int col) {
    return *min_element(tileCostsDir[row][col].begin(), tileCostsDir[row][col].end());
}

string zeros(int num, int digits) {
    string numS = to_string(num);
    if(numS.size() <= digits)
        return string(digits - numS.size(), ' ') + numS;
    return string(digits, '#');
}

void print(vector<vector<vector<int>>> tileCostsDir) {
    for(int i = 0; i < tileCostsDir.size(); i++) {
        for(int j = 0; j < tileCostsDir[0].size(); j++) {
            int cost = min(tileCostsDir, i, j);
            cout << zeros(cost, 4) << " ";
        }
        cout << endl;
    }
}

void printDir(vector<vector<vector<int>>> tileCostsDir, int dir) {
    for(int i = 0; i < tileCostsDir.size(); i++) {
        for(int j = 0; j < tileCostsDir[0].size(); j++) {
            cout << zeros(tileCostsDir[i][j][dir], 4) << " ";
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

        // cout << curr.cost << " " << curr.direction << " " << curr.row << " " << curr.col << endl;

        int solution = min(tileCostsDir, endRow, endCol);
        if(solution <= curr.cost) {
            break;
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

    // for(int i = 0; i < 4; i++) {
    //     cout << "Dir: " << i << endl;
    //     printDir(tileCostsDir, i);
    // }

    int solution = min(tileCostsDir, endRow, endCol);
    cout << solution << endl;

    int bestSpots = 0;
    queue<PQItem> q;
    for(int i = 0; i < 4; i++) {
        if(tileCostsDir[endRow][endCol][i] == solution) {
            q.push({solution, i, endRow, endCol});
        }
    }

    while(!q.empty()) {
        auto curr = q.front();
        q.pop();

        tileCostsDir[curr.row][curr.col][curr.direction] = INT32_MAX;

        // cout << curr.cost << " " << curr.direction << " " << curr.row << " " << curr.col << endl;

        if(maze[curr.row][curr.col] != 'O')
            bestSpots++;
        maze[curr.row][curr.col] = 'O';

        vector<PQItem> neighbours;
        for(auto [dir, dr, dc] : vector<tuple<int,int,int>>{{0,+1,0}, {1,0,-1}, {2,-1,0}, {3,0,+1}}) {
            int row = curr.row + dr;
            int col = curr.col + dc;
            for(int i = 0; i < 4; i++) {
                int dCost = (i != curr.direction || dir != curr.direction) ? 1001 : 1;
                // cout << "  trying to add: " << curr.cost - dCost << " " << i << " " << row << " " << col << " with cost " << tileCostsDir[row][col][i] << endl;
                if(tileCostsDir[row][col][i] == curr.cost - dCost) {
                    // cout << "  adding: " << curr.cost - dCost << " " << i << " " << row << " " << col << endl;
                    q.push({curr.cost - dCost, i, row, col});
                }
            }
        }

        for(auto prev : neighbours) {
            if(prev.cost == tileCostsDir[prev.row][prev.col][prev.direction]) {
                q.push(prev);
            }
        }
    }

    for(string row : maze) 
        cout << row << endl;

    cout << bestSpots << endl;
    return 0;
}
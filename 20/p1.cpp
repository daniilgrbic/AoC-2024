#include <iostream>
#include <cstdint>
#include <vector>
#include <queue>
#include <map>

using namespace std;

int main() {
    int startRow, startCol, endRow, endCol;
    vector<string> mem;
    string input;

    while(getline(cin, input)) {
        mem.push_back(input);
        size_t f; 
        if((f = input.find('S')) != string::npos) {
            startRow = mem.size() - 1;
            startCol = f;
        }
        if((f = input.find('E')) != string::npos) {
            endRow = mem.size() - 1;
            endCol = f;
        }
    }

    int height = mem.size();
    int width = mem.back().size();

    vector<vector<int>> distanceTo(
        height, vector<int>(width, INT32_MAX));
    
    queue<tuple<int,int,int>> q;
    q.push({0, startRow, startCol});

    int bestSave = 0;
    map<int,int> saves;
    int savesOver100 = 0;
    
    while(!q.empty()) {
        auto [d, row, col] = q.front();
        q.pop();

        if(mem[row][col] == '#')
            continue;
        if(distanceTo[row][col] <= d)
            continue;
        distanceTo[row][col] = d;
        
        for(auto [deltaRow, deltaCol] : vector<pair<int,int>>{{+1,0},{-1,0},{0,+1},{0,-1}}) {
            q.push({d + 1, row + deltaRow, col + deltaCol});
            
            int phaseRow = row + 2 * deltaRow;
            int phaseCol = col + 2 * deltaCol;
            if(phaseRow >= 0 && phaseCol >= 0 && phaseRow < height && phaseCol < width) {
                if(distanceTo[phaseRow][phaseCol] != INT32_MAX && distanceTo[phaseRow][phaseCol] + 2 < d) {
                    int save = d - 2 - distanceTo[phaseRow][phaseCol];
                    cout << "Can phase at " << phaseRow << "," << phaseCol << " to save " << save << " picoseconds" << endl;
                    bestSave = max(bestSave, save);
                    saves[save]++;
                }
            }
        } 
    }

    cout << "-----" << endl;
    for(auto [save, count] : saves) {
        cout << "There are " << count << " cheats that save " << save << " picoseconds" << endl; 
        if(save >= 100) {
            savesOver100 += count;
        }
    }
    cout << "-----" << endl;
    cout << "Time wihtout phasing: " << distanceTo[endRow][endCol] << endl;
    cout << "Best phase: " << bestSave << endl; 
    cout << "Best time: " << distanceTo[endRow][endCol] - bestSave << endl;
    cout << "Cheats that save at least 100 picoseconds: " << savesOver100 << endl;
}
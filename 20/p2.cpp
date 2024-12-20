#include <iostream>
#include <cstdint>
#include <vector>
#include <queue>
#include <map>

using namespace std;

const int CHEAT_LIMIT = 20;

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

        for(int deltaRow = - CHEAT_LIMIT; deltaRow <= CHEAT_LIMIT; deltaRow++) {
            for(int deltaCol = - CHEAT_LIMIT; deltaCol <= CHEAT_LIMIT; deltaCol++) {
                int phaseDuration = abs(deltaRow) + abs(deltaCol);
                if(phaseDuration > CHEAT_LIMIT)
                    continue;
                
                int phaseRow = row + deltaRow;
                int phaseCol = col + deltaCol;
                if(phaseRow >= 0 && phaseCol >= 0 && phaseRow < height && phaseCol < width) {
                    if(distanceTo[phaseRow][phaseCol] != INT32_MAX && distanceTo[phaseRow][phaseCol] + phaseDuration < d) {
                        int save = d - phaseDuration - distanceTo[phaseRow][phaseCol];
                        bestSave = max(bestSave, save);
                        saves[save]++;
                    }
                }
            }
        }
        
        for(auto [deltaRow, deltaCol] : vector<pair<int,int>>{{+1,0},{-1,0},{0,+1},{0,-1}}) {
            q.push({d + 1, row + deltaRow, col + deltaCol});
        } 
    }

    cout << "-----" << endl;
    for(auto [save, count] : saves) {
        if(save >= 50)
            cout << "There are " << count << " cheats that save " << save << " picoseconds" << endl; 
        if(save >= 100)
            savesOver100 += count;
    }
    cout << "-----" << endl;
    cout << "Time wihtout phasing: " << distanceTo[endRow][endCol] << endl;
    cout << "Best phase: " << bestSave << endl; 
    cout << "Best time: " << distanceTo[endRow][endCol] - bestSave << endl;
    cout << "Cheats that save at least 100 picoseconds: " << savesOver100 << endl;
}
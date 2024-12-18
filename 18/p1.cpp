#include <iostream>
#include <cstdint>
#include <vector>
#include <queue>

using namespace std;

int BYTES = 1024;
int MAP_SIZE = 71;

int bfs(vector<vector<int>>& mem) {
    int sx = 0;
    int sy = 0;
    int ex = MAP_SIZE - 1;
    int ey = MAP_SIZE - 1;

    vector<vector<int>> distanceTo(
        MAP_SIZE, vector<int>(MAP_SIZE, INT32_MAX));

    queue<tuple<int,int,int>> q;
    q.push({0, sx, sy});
    
    while(!q.empty()) {
        auto [d, x, y] = q.front();
        q.pop();

        if(mem[x][y])
            continue;
        if(distanceTo[x][y] <= d)
            continue;
        distanceTo[x][y] = d;
        
        for(auto [nx, ny] : vector<pair<int,int>>{{x+1,y},{x-1,y},{x,y+1},{x,y-1}}) {
            if(nx < 0 || nx > ex || ny < 0 || ny > ey)
                continue;
            q.push({d + 1, nx, ny});
        } 
    }

    return distanceTo[ex][ey];
}

int main(int argc, char** argv) {

    if(argc > 1)
        MAP_SIZE = atoi(argv[1]);

    if(argc > 2)
        BYTES = atoi(argv[2]);

    vector<vector<int>> mem(MAP_SIZE, vector<int>(MAP_SIZE, 0));
    int x, y;

    for(int i = 0; i < BYTES; i++) {
        cin >> x;
        cin.ignore(1);
        cin >> y;
        mem[x][y] = 1;
    }

    cout << bfs(mem) << endl;
}
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <set>

using namespace std;

int bfs(vector<string>& map, int sr, int sc) {
    int rows = map.size();
    int cols = map.front().size();

    int score = 0;
    set<pair<int,int>> reachable;

    queue<pair<int,int>> q;
    q.push({sr, sc});

    while(!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        if(map[r][c] == '9' && !reachable.contains({r, c})) {
            reachable.insert({r, c});
            score++;
            continue;
        }

        for(auto [nr, nc] : vector<pair<int,int>> {
                {r+1, c}, {r-1, c}, {r, c+1}, {r, c-1}}) {
            if(nr < 0 || nc < 0 || nr == rows || nc == cols) 
                continue;
            if(map[nr][nc] - map[r][c] != 1)
                continue;
            q.push({nr, nc});
        }
    }

    return score;
}

int main() {

    string s;
    vector<string> map;
    int score = 0;

    while(getline(cin, s)) {
        map.push_back(s);
    }

    for(int r = 0; r < map.size(); r++) {
        for(int c = 0; c < map.front().size(); c++) {
            if(map[r][c] != '0')
                continue;
            score += bfs(map, r, c);
        }
    }

    cout << score << endl;
    return 0;
}
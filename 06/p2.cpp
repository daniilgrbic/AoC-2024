#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

using Direction = pair<int,int>;
using Position = pair<int,int>;

struct Guard {
    Position pos;
    Direction dir;
    set<pair<Position,Direction>> visited;
    bool loop = false;

    Guard(Position pos) : 
        pos(pos), dir({0,-1}), visited({}) {}

    bool step(vector<string>& lab) {
        int nx = pos.first+dir.first;
        int ny = pos.second+dir.second;

        if(nx<0 || ny<0 || ny==lab.size() || nx==lab[0].size())
            return false;

        if(lab[ny][nx] == '#') {
            dir = Direction(-dir.second, dir.first);
        } 
        else {
            pos.first = nx;
            pos.second = ny;
        }

        if(visited.contains({{pos.first, pos.second}, dir}))
            loop = true;
        visited.insert({{pos.first, pos.second}, dir});

        return true && !loop;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    vector<string> lab;
    pair<int,int> guardPos;
    int obstacles = 0;

    string s;
    while(getline(cin, s)) {
        lab.push_back(s);
        if(s.find('^') != string::npos)
            guardPos = {s.find('^'), lab.size()-1};
    }

    for(int y = 0; y < lab.size(); y++) {
        for(int x = 0; x < lab[0].size(); x++) {
            if(lab[y][x] == '.') {
                lab[y][x] = '#';
                Guard guard(guardPos);
                while(guard.step(lab));
                obstacles += (int)guard.loop;
                lab[y][x] = '.';
            }
        }
        cout << y+1 << "/" << lab.size() << " rows complete" << endl;
    }

    cout << "Possible obstacles: " << obstacles << endl;

    return 0;
}

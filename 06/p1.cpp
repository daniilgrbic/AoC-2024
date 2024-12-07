#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Direction {
    int x, y;
    Direction next() { return {-y, x}; }
};

struct Guard {
    int x, y;
    Direction dir;
    int steps;

    Guard(int x, int y) : 
        x(x), y(y), dir({0,-1}), steps(1) {}

    bool step(vector<string>& lab) {
        int nx = x+dir.x;
        int ny = y+dir.y;

        if(nx<0 || ny<0 || ny==lab.size() || nx==lab[0].size())
            return false;

        if(lab[ny][nx] == '#') {
            dir = dir.next();
            return true;
        }

        if(lab[ny][nx] == '.')
            steps++;
        lab[ny][nx] = 'X';        
        x = nx;
        y = ny;
        return true;
    }
};

int main() {
    
    vector<string> lab;
    Guard* guard;

    string s;
    while(getline(cin, s)) {
        lab.push_back(s);
        if(s.find('^') != string::npos)
            guard = new Guard(s.find('^'), lab.size()-1);
    }

    while(guard->step(lab));

    cout << guard->steps << endl;

    delete guard;
    return 0;
}

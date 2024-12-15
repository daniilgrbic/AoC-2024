#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Vec2 {
    int row;
    int col;

    Vec2 operator+(Vec2& other) {
        return { row + other.row, col + other.col };
    }

    void operator+=(Vec2& other) {
        row += other.row;
        col += other.col;
    }
};

char& field(vector <string>& room, Vec2 pos) {
    return room[pos.row][pos.col];
}

Vec2 direction(char c) {
    switch(c) {
        case '>': return { 0, +1};
        case 'v': return {+1,  0};
        case '<': return { 0, -1};
        case '^': return {-1,  0};
        default: return {};
    }
}

void move(vector <string>& room, Vec2& robot, Vec2& direction) {
    Vec2 next = robot + direction;
    for(Vec2 box = next; field(room, box) != '#'; box += direction) {
        if(field(room, box) == '.') {
            swap(room[next.row][next.col], room[box.row][box.col]);
            robot += direction;
            return;
        }
    }
}

int main() {

    vector <string> room;
    Vec2 robot;
    string tmp;

    while(true) {
        getline(cin, tmp);
        if(tmp.empty())
            break;
        room.push_back(tmp);

        int found = tmp.find('@');
        if(found != string::npos) {
            robot.row = room.size() - 1;
            robot.col = found;
        }
    } 

    room[robot.row][robot.col] = '.';

    while(getline(cin, tmp)) {
        for(auto cmd : tmp) {
            Vec2 dir = direction(cmd);
            move(room, robot, dir);
        }
    }

    room[robot.row][robot.col] = '@';
    for(auto row : room) {
        cout << row << endl;
    }

    int total = 0;
    for(int row = 0; row < room.size(); row++) {
        for(int col = 0; col < room[0].size(); col++) {
            if(room[row][col] == 'O')
                total += 100 * row + col;
        }
    }

    cout << total << endl;

    return 0;
}
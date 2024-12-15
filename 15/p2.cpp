#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

struct Vec2 {
    int row;
    int col;

    Vec2 operator+(Vec2 other) {
        return { row + other.row, col + other.col };
    }

    void operator+=(Vec2 other) {
        row += other.row;
        col += other.col;
    }

    Vec2 operator*(int scale) {
        return { row * scale, col * scale };
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

// recursively returns false if tile is not movable in given direction,
// and true with a list of tiles to be moved if moving is possible
pair<int, vector<Vec2>> pushTile(vector <string>& room, Vec2 coord, Vec2 direction) {
    char tile = field(room, coord);

    if(tile == '.')
        return {true, {}};
    if(tile == '#')
        return {false, {}};
    if(tile == ']')
        coord += Vec2{0, -1};

    if(direction.row == 0) {
        // moves < and >
        auto boxes = pushTile(room, coord + 
            (direction.col == 1 ? direction * 2 : direction), direction);
        if(!boxes.first)
            return {false, {}};

        boxes.second.push_back(coord);
        return boxes;
    }
    else {
        // moves ^ and v
        auto boxes1 = pushTile(room, coord + direction, direction);
        if(!boxes1.first)
            return {false, {}};

        if(field(room, coord) != field(room, coord + direction)) {
            // if box not aligned, we actually may need to push two boxes at once
            auto boxes2 = pushTile(room, coord + direction + Vec2{0,+1}, direction);
            if(!boxes2.first)
                return {false, {}};
            boxes1.second.insert(boxes1.second.begin(), 
                boxes2.second.begin(), boxes2.second.end());
        }

        boxes1.second.push_back(coord);

        return boxes1;
    }
}

void moveBox(vector <string>& room, Vec2 box, Vec2 direction) {
    field(room, box) = '.';
    field(room, box + Vec2{0,+1}) = '.';
    field(room, box + direction) = '[';
    field(room, box + direction + Vec2{0,+1}) = ']';
}

void moveRobot(vector <string>& room, Vec2& robot, Vec2& direction) {
    Vec2 next = robot + direction;
    auto boxes = pushTile(room, next, direction);
    if(!boxes.first)
        return;

    robot = next;
    set<pair<int,int>> moved;
    for(auto box : boxes.second){
        if(!moved.count({box.row, box.col})) {
            moveBox(room, box, direction);
            moved.insert({box.row, box.col});
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
        room.push_back("");

        for(char ch : tmp) {
            switch (ch) {
                case '#':
                    room.back() += "##";
                    break;
                case '.':
                    room.back() += "..";
                    break;
                case 'O':
                    room.back() += "[]";
                    break;
                case '@':
                    room.back() += "@.";
                    break;
            }
        }

        int found = room.back().find('@');
        if(found != string::npos) {
            robot.row = room.size() - 1;
            robot.col = found;
        }
    } 

    room[robot.row][robot.col] = '@';
    for(auto row : room) {
        cout << row << endl;
    }
    room[robot.row][robot.col] = '.';

    while(getline(cin, tmp)) {
        for(auto cmd : tmp) {
            Vec2 dir = direction(cmd);
            moveRobot(room, robot, dir);
        }
    }

    room[robot.row][robot.col] = '@';
    for(auto row : room) {
        cout << row << endl;
    }

    int total = 0;
    for(int row = 0; row < room.size(); row++) {
        for(int col = 0; col < room[0].size(); col++) {
            if(room[row][col] == '[')
                total += 100 * row + col;
        }
    }
    cout << total << endl;

    return 0;
}
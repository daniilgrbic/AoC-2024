#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <map>

using namespace std;

using Plot = pair<int,int>;
using Point = pair<int,int>;

struct Line {
    Point first;
    Point second;
    int direction;
};

bool inBounds(vector<string>& region, Plot plot) {
    return
        plot.first >= 0 && plot.first < region.size() &&
        plot.second >= 0 && plot.second < region[0].size();
}

Line lineBetweenPlots(Plot a, Plot b) {
    if(a.first == b.first) {
        // vertical line
        return {
            {a.first, max(a.second, b.second)},
            {a.first + 1, max(a.second, b.second)},
            (int) (a.second > b.second) // directions 0 and 1
        };
    }
    else {
        // horizontal line
        return {
            {max(a.first, b.first), a.second},
            {max(a.first, b.first), a.second + 1},
            (int) (a.first > b.first) + 2 // directions 2 and 3
        };
    }
}

pair<int, vector<Line>> bfs(vector<string>& region, Plot plot) {
    char type = region[plot.first][plot.second];
    region[plot.first][plot.second] = tolower(type);

    vector<Line> lines;
    int area = 1;

    queue<Plot> q;
    q.push(plot);

    while(!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        for(auto [nr, nc] : vector<Plot>
                {{r+1,c}, {r-1,c}, {r,c+1}, {r,c-1}}) {
            if(!inBounds(region, {nr, nc}) || toupper(region[nr][nc]) != type)
                lines.push_back(lineBetweenPlots({r, c}, {nr, nc}));
            if(!inBounds(region, {nr, nc}) || region[nr][nc] != type)
                continue;
            q.push({nr, nc});
            region[nr][nc] = tolower(region[nr][nc]);
            area++;
        }
    }

    return {area, lines};
}

int aggregateLinesHelper(vector<Line> lines) {
    map<Point, Point> linesMap; 
    int aggregatedLines = 0;

    for(auto [p1, p2, _] : lines) {
        linesMap[p1] = p2;
    }

    while(!linesMap.empty()) {
        auto [l1p1, l1p2] = *linesMap.begin();

        if(!linesMap.contains(l1p2)) {
            linesMap.erase(l1p1);
            aggregatedLines++;
        }
        else {
            Point l2p1 = l1p2;
            Point l2p2 = linesMap[l2p1];
            linesMap.erase(l1p1);
            linesMap.erase(l2p1);
            linesMap[l1p1] = l2p2;
        }
    }

    return aggregatedLines;
}

int aggregateLines(vector<Line> lines) {
    vector<vector<Line>> categorizedLines(4);
    int aggregatedLineCount = 0;

    for(auto [p1, p2, dir] : lines) {
        categorizedLines[dir].push_back({p1, p2, dir});
    }

    for(auto lineCategory : categorizedLines) {
        aggregatedLineCount +=
            aggregateLinesHelper(lineCategory);
    }

    return aggregatedLineCount;
}

int main() {
    vector<string> region;
    int64_t totalPrice = 0;
    string tmp;

    while(getline(cin, tmp)) {
        region.push_back(tmp);
    }

    for(int r = 0; r < region.size(); r++) {
        for(int c = 0; c < region[0].size(); c++) {
            if(islower(region[r][c]))
                continue;
            auto [area, lines] = bfs(region, {r, c});
            int aggregatedLineCount = aggregateLines(lines);
            totalPrice += (int64_t) area * aggregatedLineCount;
        }
    }

    cout << totalPrice << endl;
    return 0;
}
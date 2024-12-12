#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <set>

using namespace std;

using AreaPerim = pair<int,int>;
using Plot = pair<int,int>;

bool inBounds(vector<string>& region, Plot plot) {
    return
        plot.first >= 0 && plot.first < region.size() &&
        plot.second >= 0 && plot.second < region[0].size();
}

AreaPerim bfs(vector<string>& region, Plot plot) {
    char plotType = region[plot.first][plot.second];
    region[plot.first][plot.second] = tolower(plotType);

    queue<Plot> q;
    q.push(plot);

    int area = 1;
    int perimeter = 0;

    while(!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        for(auto [nr, nc] : vector<Plot>
                {{r+1,c}, {r-1,c}, {r,c+1}, {r,c-1}}) {
            if(!inBounds(region, {nr, nc}) || toupper(region[nr][nc]) != plotType)
                perimeter++;
            if(!inBounds(region, {nr, nc}) || region[nr][nc] != plotType)
                continue;
            q.push({nr, nc});
            region[nr][nc] = tolower(region[nr][nc]);
            area++;
        }
    }

    return {area, perimeter};
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
            auto [area, perimeter] = bfs(region, {r, c});
            totalPrice += (int64_t) area * perimeter;
        }
    }

    cout << totalPrice << endl;
    return 0;
}
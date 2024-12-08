#include <iostream>
#include <ranges>
#include <vector>
#include <map>
#include <set>

using namespace std;

using Point = pair<int,int>;

vector<Point> getAntinodes(Point& a, Point& b) {
    if(a == b) {
        return {};
    }
    int df = a.first - b.first;
    int ds = a.second - b.second;
    return {
        {a.first+df, a.second+ds},
        {b.first-df, b.second-ds}
    };
}

int main() {
    map<int, vector<Point>> antennae;
    vector<string> city;
    set<Point> antinodes;
    string s;

    while(getline(cin, s)) {
        city.push_back(s);
        for(int i = 0; i < s.size(); i++) {
            char type = city.back().at(i);
            if(type != '.') {
                antennae[type].push_back({city.size()-1, i});
            }
        }
    }

    for(auto& [type, coords] : antennae) {
        for(auto const& [a, b] : views::cartesian_product(coords, coords)) {
            for(auto an : getAntinodes(a, b)) {
                antinodes.insert(an);
            }
        }
    }

    antinodes = 
        antinodes |
        views::filter([&city](Point p) {
            return p.first >= 0 && p.first < city.size() &&
                p.second >= 0 && p.second < city[0].size();
        }) |
        ranges::to<set>();

    cout << antinodes.size() << endl;
    return 0;
}
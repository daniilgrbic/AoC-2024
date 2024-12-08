#include <iostream>
#include <ranges>
#include <vector>
#include <map>
#include <set>

using namespace std;

using Point = pair<int,int>;

bool inBounds(Point& p, pair<int,int>& bounds) {
    return p.first >= 0 && p.first < bounds.first &&
        p.second >= 0 && p.second < bounds.second;
}

vector<Point> getAntinodes(Point& a, Point& b, pair<int,int>& bounds) {
    vector<Point> antinodes;
    int df = a.first - b.first;
    int ds = a.second - b.second;
    for(Point p = a; inBounds(p, bounds); p.first+=df, p.second+=ds)
        antinodes.push_back(p);
    for(Point p = b; inBounds(p, bounds); p.first-=df, p.second-=ds)
        antinodes.push_back(p);
    return antinodes;
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

    pair<int,int> cityBounds = 
        {city.size(), city[0].size()};
    for(auto& [type, coords] : antennae) {
        for(auto const& [a, b] : views::cartesian_product(coords, coords)) {
            if(a != b) {
                for(auto an : getAntinodes(a, b, cityBounds)) {
                    antinodes.insert(an);
                }
            }
        }
    }

    cout << antinodes.size() << endl;
    return 0;
}

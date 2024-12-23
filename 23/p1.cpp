#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

int main() {
    map<string,set<string>> graph;
    int total = 0;
    string input;

    while(cin >> input) {
        string a = input.substr(0, 2);
        string b = input.substr(3, 2);
        graph[a].insert(b);
        graph[b].insert(a);
    }

    for(auto& [a, neighbours]: graph) {
        for(auto& b: neighbours) {
            if(b <= a)
                continue;
            for(auto& c: neighbours) {
                if(c <= b || !graph[c].contains(b))
                    continue;
                if(a.starts_with('t') || b.starts_with('t') || c.starts_with('t')) {
                    cout << a << " " << b << " " << c << endl;
                    total++;
                }
                    
            }
        }
    }

    cout << total << endl;
    return 0;
}

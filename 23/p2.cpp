#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

int main() {
    map<string,set<string>> graph;
    set<set<string>> cliques, newCliques;
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
                cliques.insert({a, b, c});
            }
        }
    }

    cout << "There are " << cliques.size() << " cliques of size " << cliques.begin()->size() << endl;

    do {

        // try to expand every clique by 1 more element, drop the clique if this is impossible
        for(auto clique: cliques) {

            // try to add an element from the clique's first element neighbours
            for(string nextComp: graph[*clique.begin()]) {
                
                // this potential new element should be connected to all elements in the clique
                int good = true;
                for(string cliqueComp: clique) {
                    if(!graph[nextComp].contains(cliqueComp)) {
                        good = false;
                        break;
                    }
                }

                if(good) {
                    clique.insert(nextComp);
                    newCliques.insert(clique);
                    break;
                }
            }
        }

        cliques.swap(newCliques);
        newCliques.clear();
        cout << "There are " << cliques.size() << " cliques of size " << cliques.begin()->size() << endl;

    } while(cliques.size() > 1);

    string password;
    for(string part: *cliques.begin()) {
        if(password.size())
            password += ",";
        password += part;
    }
    cout << password << endl;

    return 0;
}

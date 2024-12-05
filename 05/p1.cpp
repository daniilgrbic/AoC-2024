#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>

using namespace std;

bool checkUpdate(vector<int>& update, map<int,set<int>>& rules) {
    for(int page = 0; page+1 < update.size(); page++) {
        if(!rules[update[page]].contains(update[page+1]))
            return false;
    }
    return true;
}

int main() {
    string line;
    int resultSum = 0;
    map<int,set<int>> rules;

    while(getline(cin, line) && line != "") {
        stringstream ss(line);
        int first, second;
        char delimiter;

        ss >> first >> delimiter >> second;
        rules[first].insert(second);
    }

    while(getline(cin, line)) {
        stringstream ss(line);
        vector<int> update;
        string page;

        while(getline(ss, page, ',')) {
            update.push_back(stoi(page));
        }

        if(checkUpdate(update, rules)) {
            resultSum += update[update.size()/2];
        }
    }

    cout << resultSum << endl;
    return 0;
}
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>

using namespace std;

int main() {
    string line;
    int resultSum = 0;
    map<int,set<int>> forbidden;

    while(getline(cin, line) && line != "") {
        stringstream ss(line);
        int first, second;
        char delimiter;

        ss >> first >> delimiter >> second;
        forbidden[second].insert(first);
    }

    while(getline(cin, line)) {
        stringstream ss(line);
        vector<int> update;
        string page;

        while(getline(ss, page, ',')) {
            update.push_back(stoi(page));
        }

        bool sorted = true;
        int i = 0;
        while(i+1 != update.size()) {
            int& curr = update[i];
            int& next = update[i+1];

            if (forbidden[curr].contains(next)) {
                swap(curr, next);
                sorted = false;
                if(i) i--;
            }
            else {
                i++;
            }
        }

        if(!sorted) {
            resultSum += update[update.size()/2];
        }
    }

    cout << resultSum << endl;
    return 0;
}
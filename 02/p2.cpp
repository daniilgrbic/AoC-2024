#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <ranges>
#include <cmath>

using namespace std;

int main() {
    int total{};
    string line;

    while(getline(cin, line)) {
        istringstream iss(line);

        auto nums = 
            ranges::istream_view<int>(iss) | 
            ranges::to<vector>();

        for(int i = 0; i < nums.size(); i++) {
            auto numsCopy = nums;
            numsCopy.erase(numsCopy.begin() + i);

            auto diffs = 
                numsCopy |
                views::adjacent_transform<2>(
                    [](int a, int b){return b - a;});
            
            bool safe = ranges::all_of(diffs, [&diffs](int n){
                return 
                    signbit(n) == signbit(diffs[0]) &&
                    abs(n) >= 1 && 
                    abs(n) <= 3;
            });

            if(safe) {
                total++;
                break;
            }
        }
    }

    cout << total << endl;

    return 0;
}
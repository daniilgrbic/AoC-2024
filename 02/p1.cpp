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

        auto diffs = 
            ranges::istream_view<int>(iss) |
            ranges::to<vector>() |
            views::adjacent_transform<2>([](int a, int b){return b - a;});

        total += ranges::all_of(diffs, [&diffs](int n){
            return 
                signbit(n) == signbit(diffs[0]) &&
                abs(n) >= 1 && 
                abs(n) <= 3;
        });
    }

    cout << total << endl;

    return 0;
}

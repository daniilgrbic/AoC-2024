#include <iostream>
#include <cmath>
#include <list>

using namespace std;

int digitCount(int64_t n) {
    if(n > 0)
        return 1 + digitCount(n / 10);
    return 0;
}

int main() {
    
    list <int64_t> stones;
    int s, digits;

    while(cin >> s) {
        stones.push_back(s);
    }

    for(int i = 0; i < 25; i++) {
        for(auto it = stones.begin(); it != stones.end(); it++) {
            if(*it == 0) {
                *it += 1;
            }
            else if((digits = digitCount(*it)) % 2 == 0) {
                stones.insert(it, *it / (int64_t) pow(10, digits/2));
                *it %= (int64_t) pow(10, digits/2);
            }
            else {
                *it *= 2024;
            }
        }
    }

    cout << stones.size() << endl;
    return 0;
}
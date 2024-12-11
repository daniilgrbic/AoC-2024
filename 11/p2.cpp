#include <iostream>
#include <cmath>
#include <map>

using namespace std;

int digitCount(int64_t n) {
    if(n > 0)
        return 1 + digitCount(n / 10);
    return 0;
}

int main() {
    
    map <int64_t, int64_t> stones;
    int64_t totalStones = 0;
    int64_t tmp;
    int digits;

    while(cin >> tmp) {
        stones[tmp]++;
    }

    for(int i = 0; i < 75; i++) {
        map <int64_t, int64_t> newStones;
        for(auto [stone, count] : stones) {
            if(stone == 0) {
                newStones[1] = count;
            }
            else if((digits = digitCount(stone)) % 2 == 0) {
                newStones[stone / (int64_t) pow(10, digits/2)] += count;
                newStones[stone % (int64_t) pow(10, digits/2)] += count;
            }
            else {
                newStones[stone * 2024] = count;
            }
        }
        stones.swap(newStones);
    }

    for(auto [stone, count] : stones) {
        totalStones += count;
    }

    cout << totalStones << endl;
    return 0;
}
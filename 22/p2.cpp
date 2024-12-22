#include <iostream>
#include <queue>
#include <map>
#include <set>

using namespace std;

const int64_t MOD = 16777216;

using tuple4 = tuple<int64_t, int64_t, int64_t, int64_t>;

int64_t nextSecret(int64_t secret) {
    secret ^= secret * 64;
    secret %= MOD;
    secret ^= secret / 32;
    secret %= MOD;
    secret ^= secret * 2048;
    secret %= MOD;
    return secret;
}

int main() {
    map<tuple4, int64_t> sequences;
    int64_t bananas = 0;
    int64_t num;

    while(cin >> num) {
        deque<int> lastFour;
        set<tuple4> visited;
        lastFour.push_back(num);
        for(int i = 0; i < 2000; i++) {
            num = nextSecret(num);
            lastFour.push_back(num);
            if(lastFour.size() > 4) {
                tuple4 t = {
                    lastFour[1]%10 - lastFour[0]%10, lastFour[2]%10 - lastFour[1]%10, 
                    lastFour[3]%10 - lastFour[2]%10, lastFour[4]%10 - lastFour[3]%10
                };
                if(!visited.contains(t)) {
                    sequences[t] += num % 10;
                    bananas = max(bananas, sequences[t]);
                    visited.insert(t);
                }
                lastFour.pop_front();
            }
        }
    }

    cout << bananas << endl;
    return 0;
}

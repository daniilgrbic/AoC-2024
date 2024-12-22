#include <iostream>

using namespace std;

const int64_t MOD = 16777216;

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
    int64_t sum = 0;
    int64_t num;

    while(cin >> num) {
        cout << num << ": ";
        for(int i = 0; i < 2000; i++)
            num = nextSecret(num);
        cout << num << endl;
        sum += num;
    }

    cout << "-----" << endl;
    cout << sum << endl;
    return 0;
}

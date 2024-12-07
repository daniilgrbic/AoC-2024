#include <iostream>
#include <sstream>
#include <ranges>
#include <list>

using namespace std;

int64_t concatenate(int64_t a, int64_t b) {
    int64_t factor = 1;
    while(factor <= b)
        factor *= 10;
    return a * factor + b;
}

bool check(int64_t target, list<int64_t>& nums) {
    if(nums.size() == 1)
        return nums.front() == target;
    
    if(nums.front() > target)
        return false;

    int64_t a = nums.front(); nums.pop_front();
    int64_t b = nums.front(); nums.pop_front();

    nums.push_front(a + b);
    bool check1 = check(target, nums);
    nums.front() = a * b;
    bool check2 = check(target, nums);
    nums.front() = concatenate(a, b);
    bool check3 = check(target, nums);
    nums.pop_front();

    nums.push_front(b);
    nums.push_front(a);

    return check1 || check2 || check3;
}

int main() {
    string s;
    int64_t totalResult = 0;

    while(getline(cin, s)) {
        istringstream iss(s);
        
        int64_t target;
        iss >> target;
        iss.ignore(1);

        list<int64_t> nums =
            ranges::istream_view<int64_t>(iss) |
            ranges::to<list>();
        
        if(check(target, nums))
            totalResult += target;
    }

    cout << "Total calibration result: " << totalResult << endl;
    return 0;
}

#include <iostream>
#include <algorithm>
#include <set>
using namespace std;
int main() {
    int n, k;
    cin >> n >> k;
    set<unsigned long> nums;
    unsigned long num;
    for (int i = 0; i < n; ++i) {
        cin >> num;
        nums.insert(num);
    }
    unsigned long long last = 0;
    auto it = nums.begin();
    for (int i = 0; i < k; ++i) {
        if (it != nums.end()) {
            cout << *it - last << endl;
            last = *it;
            it++;
        } else 
            cout << 0 << endl;
    }
    return 0;
}
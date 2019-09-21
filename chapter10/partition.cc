#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

bool islonger(string s) {
    return s.length() >= 5;
}

int main(int argc, char const *argv[])
{
    vector<string> words{"the", "quick", "red", "fox", "jumps", "over",
    "the", "slow", "red", "turtle"};
    auto iter = partition(words.begin(), words.end(), islonger);
    for (auto it = words.begin(); it != iter; ++it)
        cout << *it << " ";
    cout << endl;
    return 0;
}

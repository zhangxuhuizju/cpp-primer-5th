#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

auto g(int num) -> int {
    auto f = [num](){return num + 10;};
    return f();
}

int main(int argc, char const *argv[])
{
    auto f = [](const int &a, const int &b){return a + b;};

    cout << f(1,2) << ' ' << g(5) << endl;

    vector<string> words{"the", "quick", "red", "fox", "jumps", "over",
    "the", "slow", "red", "turtle"};

    int res = count_if(words.begin(), words.end(),
            [](const string& s){return s.size() > 6;});
    
    cout << words.size() << ' ' << res << endl;

    int v = 3;
    auto decrease = [=]()mutable->bool{if (v > 0) --v; return v > 0;};
    cout << decrease() << ' ' << decrease() << ' ' << decrease() << ' ' << decrease() << endl;
    return 0;
}

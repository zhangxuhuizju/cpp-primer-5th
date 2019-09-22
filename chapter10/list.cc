#include <list>
#include <iostream>
#include <algorithm>

using namespace std;

void elimDumps(list<string> &lst) {
    lst.sort();
    lst.unique();
}

int main(int argc, char const *argv[])
{
    list<string> lst{"the", "quick", "red", "fox", "jumps", "over",
    "the", "slow", "red", "turtle"};

    elimDumps(lst);
    for (string s : lst)
        cout << s << ' ';
    cout << endl;
    return 0;
}

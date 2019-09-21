#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <list>
#include <functional>
using namespace std;

int main(int argc, char const *argv[])
{
    string a[10] = {"love","love8","love","love","love","h","diuw","diuwudhg257","love","d"};
    vector<string> v1(a, a+10);
    list<string> l1;

    sort(v1.begin(), v1.end());
    unique_copy(v1.cbegin(), v1.cend(), inserter(l1,l1.end()));

    for_each(l1.cbegin(), l1.cend(), [](const string &s){cout << s << ' ';});
    return 0;
}

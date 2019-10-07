#include <iostream>
#include <vector>
#include <list>
#include <string>
using namespace std;

template <typename T, typename... Args>
void Foo(const T&, const Args&...args) {
    cout << sizeof...(Args) << ' ' << sizeof...(args) << endl;
}

int main(int argc, char const *argv[])
{
    int i = 0;
    double d = 3.14;
    string s = "how";
    Foo(i, s, 42, d);
    Foo(s, 42, "hi");
    Foo(d, s);
    Foo("hi");
    return 0;
}

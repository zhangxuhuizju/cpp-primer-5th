#include <iostream>
#include <string>
using namespace std;

class A {
public:
    A(string name):name(name) {}
    string word = "haha";
private:
    string name;
};

int main(int argc, char const *argv[])
{
    A a = A("hello");
    const string A::*n = &A::word;
    auto s = a.*n;
    cout << s << endl;
    string s = "la";
    s.empty();
    return 0;
}

#include <iostream>
#include <string>
using namespace std;

// extern int j = 2;
int main(int argc, char const *argv[])
{
    // int input_value;
    // cin >> input_value;
    // double pi = 3.14;
    // const int &pp = pi;
    // int i = 10;
    // const int &i1 = i;
    // int &i2 = i;
    // i2 = 0;
    // bool c = true;
    // bool d = -c;
    // cout << d << endl;
    // int k = 0;
    // k = {true};
    // const int m = 42;
    // int *i = const_cast<int*>(&m);
    // (*i) = 50;
    // cout << *(&m) << " " << *i << endl;
    // cout << static_cast<const void *>(&m) << " "  << static_cast<const void *>(i) << endl;
    int m = 97;
    int *s = &m;
    char *i = reinterpret_cast<char*>(s);
    string ss(i);
    cout << ss << endl;
    return 0;
}

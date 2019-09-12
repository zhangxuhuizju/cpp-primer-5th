#include <iostream>
using namespace std;

// extern int j = 2;
int main(int argc, char const *argv[])
{
    // int input_value;
    // cin >> input_value;
    // double pi = 3.14;
    // const int &pp = pi;
    int i = 10;
    const int &i1 = i;
    int &i2 = i;
    i2 = 0;
    cout << i1 << endl;
    return 0;
}

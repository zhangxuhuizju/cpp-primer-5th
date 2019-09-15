#include <iostream>
#include <string>
#include <vector>
using namespace std;

int add(int a, int b)
{
	return a+b;
}
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
int divide(int a, int b) { return b != 0 ? a / b : 0; }

int main(int argc, char const *argv[])
{
    vector<int(*)(int, int)> v{add, subtract, multiply, divide};
    for (auto f : v)
        cout << f(2, 2) << endl;    
    return 0;
}


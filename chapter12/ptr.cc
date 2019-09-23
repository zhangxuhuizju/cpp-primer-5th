#include <vector>
#include <string>
#include <iostream>
using namespace std;

vector<int> *get() {
    return new vector<int>;
}

void input(vector<int> *p, istream &os) {
    int i;
    while (os >> i)
        p->push_back(i);
}

void output(vector<int> *p) {
    for (auto i : *p)
        cout << i << ' ';
    cout << endl;
}

int main(int argc, char const *argv[])
{
    auto ptr = get();
    input(ptr, cin);
    output(ptr);
    delete ptr;
    return 0;
}

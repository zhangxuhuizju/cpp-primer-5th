#include <vector>
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
using namespace std;

int main(int argc, char const *argv[])
{
    ifstream file("lambda.cc");
    istream_iterator<string> iter(file), eof;
    vector<string> vec(iter, eof);

    ostream_iterator<string> os(cout);
    copy(vec.begin(), vec.end(), os);
    return 0;
}

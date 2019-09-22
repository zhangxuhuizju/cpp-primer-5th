#include <map>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>
using namespace std;

int main(int argc, char const *argv[])
{
    vector<string> v{"haha"};
    multiset<string> c;
    //copy(c.begin(), c.end(), inserter(v, v.end()));
    copy(v.begin(), v.end(), inserter(c, c.end()));
    //copy(v.begin(), v.end(), back_inserter(c));
    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

int main(int argc, char const *argv[])
{
    int n;
    //vector<unsigned int> time;
    map<unsigned int, unsigned int> count;
    cin >> n;
    //unsigned long M = 0;
    unsigned int x;
    unsigned int delay;
    for (int i = 0; i != n; ++i) {
        cin >> x >> delay;        
        count[delay] += x;
        //time.insert(time.end(), x, delay);
    }
    unsigned long result = 0;
    while (count.size() != 0) {
        auto first = count.begin();
        auto second = --count.end();
        if (first->first + second->first > result)
            result = first->first + second->first;
        if (first == second) {
            count.erase(first);
        } else if(first->second == second->second){
            count.erase(first);
            count.erase(second);
        } else if (first->second > second->second) {
            count[first->first] -= count[second->first];
            count.erase(second);
        } else {
            count[second->first] -= count[first->first];
            count.erase(first);
        }
    }
    cout << result << endl;
    return 0;
}

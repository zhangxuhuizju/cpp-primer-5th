#include <map>
#include <set>
#include <algorithm>
#include <cctype>
#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    map<string, size_t> word_count;
    string word;
    set<string> exclude = {"the", "an"}; //....
    while (cin >> word) {
        for (auto &it : word)
            tolower(it);
        word.erase(remove_if(word.begin(), word.end(), 
            ::ispunct), word.end());  //注意此处的ispunct需要全局空间的，不是std的！
        if (exclude.find(word) == exclude.end())
            ++word_count[word];
    }
    return 0;
}

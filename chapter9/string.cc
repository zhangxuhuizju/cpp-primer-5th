#include <string>
#include <iostream>
using namespace std;

void replace(string &s, string oldVal, string newVal) {
    int pos = -newVal.size();
    while ((pos = s.find(oldVal, pos + newVal.size())) != string::npos) {
        //cout << pos << endl;
        s.replace(pos, oldVal.size(), newVal);
        //cout << s << endl;
    }
}

int main(int argc, char const *argv[])
{   
    string s = "tho tho thru tho thru hhh";
    replace(s, "tho", "thought");
    cout << s << endl;
    return 0;
}

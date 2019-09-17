#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char const *argv[])
{
    string fileName = "xxx"; //xxx代替为filename即可
    vector<string> v;
    ifstream in(fileName);
    if (in) {
        string buf;
        while(getline(in, buf))
            v.push_back(buf);
    }else {
        cerr << "Cannot open the file: " << fileName << endl;
    }
    return 0;
}


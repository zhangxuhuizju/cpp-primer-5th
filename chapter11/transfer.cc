#include <fstream>
#include <map>
#include <algorithm>
#include <sstream>
using namespace std;

map<string, string> buildMap(ifstream &map_file) {
    map<string, string> trans_map;
    string key, value;
    while (map_file >> key && getline(map_file, value)) {
        if (value.size() <= 1)
            throw runtime_error("no rule for" + key);
        else
            trans_map[key] = value.substr(1);  //skip the ' ' front
    }
    return trans_map;
}

const string &
transform(const string &s, const map<string, string> &m) {
    auto it = m.find(s);
    if (it == m.cend())
        return s;
    else
        return it->second;
}

void word_transform(ifstream &map_file, ifstream &input, ofstream &output) {
    auto trans_map = buildMap(map_file);
    string text;
    while (getline(input, text)) {
        istringstream stream(text);
        string word;
        bool firstword = true;
        while (stream >> word) {
            if (firstword)
                firstword = false;
            else
                output << ' ';
            output << transform(word, trans_map);
        }
        output << endl;
    }
}

int main(int argc, char const *argv[])
{
    ifstream map_file("input1.txt"), input("input2.txt");
    ofstream output("output.txt", ofstream::app);
    word_transform(map_file, input, output);
    return 0;
}

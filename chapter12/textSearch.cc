#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <memory>
using namespace std;

class QueryResult;
class TextQuery{
public:
    using line_no = vector<string>::size_type;
    TextQuery(ifstream&);
    QueryResult query(const string &s) const;
private:
    shared_ptr<vector<string>> file;
    map<string, shared_ptr<set<line_no>>> linesMap;
};

class QueryResult{
friend ostream& print(ostream &os, const QueryResult& qr);
public:
    QueryResult(string s,
                shared_ptr<vector<string>> f,
                shared_ptr<set<TextQuery::line_no>> l):
                soughtWord(s), file(f), lines(l){}           
    set<TextQuery::line_no>::iterator begin(){
        return lines->begin();
    }
    set<TextQuery::line_no>::iterator end(){
        return lines->end();
    }
    shared_ptr<vector<string>> get_file(){
        return shared_ptr<vector<string>>(file);
    }
private:
    shared_ptr<vector<string>> file;
    shared_ptr<set<TextQuery::line_no>> lines;
    string soughtWord;
};


TextQuery::TextQuery(ifstream &infile):file(make_shared<vector<string>>()) {
    string text;
    while (getline(infile, text)) {
        file->push_back(text);
        line_no lineNumber = file->size();
        istringstream line(text);
        string word;
        while (line >> word) {
            auto &lines = linesMap[word];
            if (!lines)
                lines = make_shared<set<line_no>>();
            lines->insert(lineNumber);
        }
    }
}

QueryResult TextQuery::query(const string &s) const {
    if (linesMap.find(s) == linesMap.end())
        return QueryResult(s, file, make_shared<set<line_no>>());
    else
        return QueryResult(s, file, linesMap.find(s)->second);
}

ostream& print(ostream &os, const QueryResult& qr) {
    os << qr.soughtWord << " occurs " << qr.lines->size() << " ";
    if (qr.lines->size() <= 1)
        os << "time" << endl;
    else
        os << "times" << endl;
    for (auto num : *qr.lines)
        os << "\t(line" << num << ") "
        << (*qr.file)[num-1] << endl;
    return os;
}

void runQueries(ifstream &infile) {
    //in file is an ifstream, point to the file we want to handle
    TextQuery tq(infile);

    while (true) {
        cout << "enter word to look for, or q to quit: ";
        string s;
        if (!(cin >> s) || s == "q")
            break;
        print(cout, tq.query(s)) << endl;
    }

}

int main(int argc, char const *argv[])
{
    ifstream in("diff.txt");
    runQueries(in);
    in.close();
    return 0;
}

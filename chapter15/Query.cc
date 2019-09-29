#include "Query.h"

TextQuery::TextQuery(std::ifstream& in): 
file(new std::vector<std::string>) {
    std::string text;
    while (std::getline(in, text)) {
        file->push_back(text);      //保存该行文本;
        line_no n = file->size();   //行号
        std::istringstream line(text);
        std::string word;
        while (line >> word) {
            //std::cout << word << std::endl;
            //如果单词不在w_to_l中，在w_to_l中加一项
            auto &lines = w_to_l[word];
            if (!lines)
                lines = std::make_shared<std::set<line_no>>();
            lines->insert(n);
        }
    }
}

QueryResult TextQuery::query(const std::string& word) const {
    if (w_to_l.find(word) == w_to_l.end())
        return QueryResult(word,std::make_shared<std::set<line_no>>(), file);
    else 
        return QueryResult(word, w_to_l.find(word)->second, file);
}

std::ostream& print(std::ostream& os, const QueryResult& qr) {
    os << qr.sought << " ouccurs " << qr.lines->size() << " "
       << (qr.lines->size() > 1 ? "times" : "time") << std::endl;
    for (auto num : *qr.lines) {
        os << "\t(line" << num << ") "
           << (*qr.file)[num-1] << std::endl;
    }
    return os;
}

std::ostream & operator<<(std::ostream &os, const Query &query) {
    //利用指向query_base的指针进行rep的虚调用
    return os << query.rep();
}

inline Query::Query(const std::string &s):q(new WordQuery(s)){}

inline Query operator&(const Query &l, const Query &r) {
    return std::shared_ptr<Query_base>(new AndQuery(l, r));
}

inline Query operator|(const Query& l, const Query& r) {
    return std::shared_ptr<Query_base>(new OrQuery(l, r));
}

inline Query operator~(const Query& q) {
    return std::shared_ptr<Query_base>(new NotQuery(q));
}

QueryResult OrQuery::eval(const TextQuery& tq) const {
    auto left = lhs.eval(tq);
    auto right = rhs.eval(tq);
    auto result = std::make_shared<std::set<line_no>>(left.begin(), left.end());
    result->insert(right.begin(), right.end());
    return QueryResult(rep(), result, left.getfile());
}

QueryResult AndQuery::eval(const TextQuery& tq) const {
    auto left = lhs.eval(tq);
    auto right = rhs.eval(tq);
    auto result = std::make_shared<std::set<line_no>>();
    std::set_intersection(left.begin(), left.end(),
                right.begin(), right.end(), 
                std::inserter(*result, result->begin()));
    return QueryResult(rep(), result, left.getfile());
}

QueryResult NotQuery::eval(const TextQuery& tq) const {
    auto last = query.eval(tq);
    auto result = std::make_shared<std::set<line_no>>();
    auto full = std::make_shared<std::set<line_no>>();
    auto lines = last.getfile()->size();
    for (auto i = 1; i <= lines; ++i)
        full->insert(i);
    std::set_difference(full->begin(), full->end(), 
            last.begin(), last.end(),
            std::inserter(*result, result->begin()));
    return QueryResult(rep(), result, last.getfile());
}

void runQueries(std::ifstream &infile) {
    TextQuery tq(infile);

    while (true) {
        std::cout << "Executing Query for, or q to quit: ";
        std::string s;
        if (!(std::cin >> s) || s == "q")
            break;
        print(std::cout, tq.query(s)) << std::endl;
    }

}

int main(int argc, char const *argv[])
{
    std::ifstream in("test.txt");
    TextQuery tq(in);
    in.close();
    Query q = Query("fiery") & ~Query("bird") | Query("wind");
    print(std::cout, q.eval(tq)) << std::endl;
    
    return 0;
}

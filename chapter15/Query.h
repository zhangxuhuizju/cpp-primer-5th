#ifndef QUERY
#define QUERY
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <algorithm>

class QueryResult;

class TextQuery {
public:
    using line_no = std::vector<std::string>::size_type;
    TextQuery(std::ifstream &);
    QueryResult query(const std::string&) const;
private:
    std::shared_ptr<std::vector<std::string>> file;
    //每个单词到行号的集合映射
    std::map<std::string, std::shared_ptr<std::set<line_no>>> w_to_l;
};

class QueryResult {
friend std::ostream& print(std::ostream&, const QueryResult&);
public:
    QueryResult(std::string s, std::shared_ptr<std::set<TextQuery::line_no>> l,
                std::shared_ptr<std::vector<std::string>> f):
                sought(s), lines(l), file(f){};
    std::set<TextQuery::line_no>::iterator begin() {
        return lines->begin();
    }
    std::set<TextQuery::line_no>::iterator end() {
        return lines->end();
    }
    std::shared_ptr<std::vector<std::string>> getfile() {
        return file;
    }
private:
    std::string sought;     //查找的单词
    std::shared_ptr<std::set<TextQuery::line_no>> lines;    //出现的行号
    std::shared_ptr<std::vector<std::string>> file;
};

class Query_base {
    friend class Query;
protected:
    using line_no = TextQuery::line_no;
    virtual ~Query_base() = default;
private:
    //eval返回与房前Query匹配的QueryResult
    virtual QueryResult eval(const TextQuery &) const = 0;
    //rep表示查询的一个string
    virtual std::string rep() const = 0;
};

class Query {
    friend Query operator~(const Query&);
    friend Query operator|(const Query&, const Query&);
    friend Query operator&(const Query&, const Query&);
public:
    Query(const std::string&);      //创建一个新的wordQuery
    //接口函数，调用相应的query_base操作
    QueryResult eval(const TextQuery &tq) const {
        return q->eval(tq);
    }
    std::string rep() const {return q->rep();}
private:
    Query(std::shared_ptr<Query_base> query) : q(query) {}
    std::shared_ptr<Query_base> q;
};

class WordQuery : public Query_base {
    friend class Query;
    WordQuery(const std::string &s):query_word(s) {}
    QueryResult eval(const TextQuery &tq) const override {
        return tq.query(query_word);
    }
    std::string query_word;
    std::string rep() const override {return query_word;}
};

class NotQuery : public Query_base {
    friend Query operator~(const Query&);
    NotQuery(const Query &q):query(q){}
    std::string rep() const override {
        return "~(" + query.rep() + ")";
    }
    QueryResult eval(const TextQuery&) const override;
    Query query;
};

class BinaryQuery : public Query_base{
protected:
    BinaryQuery(const Query &l, const Query &r, std::string s):
        lhs(l), rhs(r), opSym(s){}
    std::string rep() const override {
        return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")";
    }
    Query lhs, rhs;         //左侧和右侧运算对象
    std::string opSym;      //运算符名字
};

class AndQuery : public BinaryQuery {
    friend Query operator&(const Query&, const Query&);
    AndQuery(const Query &l, const Query &r):
        BinaryQuery(l, r, "&"){}
    QueryResult eval(const TextQuery&) const override;
};

class OrQuery : public BinaryQuery {
    friend Query operator|(const Query&, const Query&);
    OrQuery(const Query &l, const Query &r):
        BinaryQuery(l, r, "|"){}
    QueryResult eval(const TextQuery&) const override;
};

std::ostream & operator<<(std::ostream &os, const Query &query);
Query operator~(const Query&);
Query operator|(const Query&, const Query&);
Query operator&(const Query&, const Query&);
std::ostream& print(std::ostream&, const QueryResult&);

#endif
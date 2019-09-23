#ifndef STRBLOB
#define STRBLOB

#include <memory>
#include <string>
#include <vector>
using namespace std;

class StrBlobPtr;
class StrBlob {
    friend class StrBlobPtr;
public:
    using size_type = vector<string>::size_type;
    StrBlob();
    StrBlob(initializer_list<string> il);
    size_type size() const {return data->size();}
    bool empty() const {return data->empty();}
    void push_back(const string &s) {data->push_back(s);}
    void pop_back();
    string &front();
    const string &front() const;
    string &back();
    const string &back() const;
    StrBlobPtr begin();
    StrBlobPtr end();
private:
    shared_ptr<vector<string>> data;
    void check(size_type i, const string &msg) const;
};


class StrBlobPtr {
public:
    StrBlobPtr():curr(0){}
    StrBlobPtr(StrBlob &a, size_t sz = 0):
            wptr(a.data), curr(sz) {}
    string& deref() const;
    StrBlobPtr& incr();   //前缀递增
private:
    //若检查成功，返回一个指向vector的shared_ptr
    shared_ptr<vector<string>>
        check(size_t, const string &) const;
    //保存一个weak_ptr
    weak_ptr<vector<string>> wptr;
    size_t curr;
};

#endif
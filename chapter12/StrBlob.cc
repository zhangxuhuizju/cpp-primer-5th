#include "StrBlob.h"

StrBlob::StrBlob():data(make_shared<vector<string>>()){}

StrBlob::StrBlob(initializer_list<string> il):
        data(make_shared<vector<string>>(il)){}

void StrBlob::check(size_type i, const string &msg) const {
    if (i >= data->size())
        throw out_of_range(msg);
}

string& StrBlob::front() {
    check (0, "front on empty StrBlob");
    return data->front();
}

const string& StrBlob::front() const{
    check (0, "front on empty StrBlob");
    return data->front();
}


string& StrBlob::back() {
    check (0, "back on empty StrBlob");
    return data->back();
}

const string& StrBlob::back() const{
    check (0, "back on empty StrBlob");
    return data->back();
}

void StrBlob::pop_back() {
    check (0, "pop_back on empty StrBlob");
    data->pop_back();
}

StrBlobPtr StrBlob::begin(){
	return StrBlobPtr(*this, 0);
}

StrBlobPtr StrBlob::end(){
	auto ret = StrBlobPtr(*this, data->size());
	return ret;
}

shared_ptr<vector<string>> 
StrBlobPtr::check(size_t i, const string& msg) const {
    auto ret = wptr.lock();  //is vector exist?
    if (!ret)
        throw runtime_error("unbound strBlobPtr");
    if (i >= ret->size())
        throw out_of_range(msg);
    return ret;
}

string& StrBlobPtr::deref() const {
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}

//返回递增后的对象的引用
StrBlobPtr& StrBlobPtr::incr() {
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}
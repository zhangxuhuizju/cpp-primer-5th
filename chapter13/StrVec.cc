#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>

class StrVec{
public:
    StrVec():
        elements(nullptr), first_free(nullptr),cap(nullptr){}
    StrVec(std::initializer_list<std::string>);
    StrVec(const StrVec&);                  //拷贝构造函数
    StrVec(StrVec &&) noexcept;             //移动构造函数
    StrVec& operator=(StrVec &&) noexcept;  //移动赋值运算符
    StrVec& operator=(const StrVec&);       //拷贝赋值运算符
    ~StrVec();                              //析构函数
    void push_back(const std::string&);     //拷贝元素
    void push_back(std::string &&);         //移动拷贝元素
    size_t size() const {return first_free-elements;}
    size_t capacity() const {return cap-elements;}
    std::string *begin() const{return elements;}
    std::string *end() const{return first_free;}
    void reserve(size_t n);
    void resize(size_t s, const std::string& = std::string());
private:
    static std::allocator<std::string> alloc;   //allocate elements
    //被添加元素的函数所使用
    void chk_n_alloc() {
        if (size() == capacity()) reallocate();
    }
    //工具函数，被拷贝构造函数、赋值运算符和析构函数使用
    std::pair<std::string*, std::string*> alloc_n_copy
        (const std::string*, const std::string*);
    void free();                //销毁元素并且释放内存
    void reallocate(size_t newSize = 0);          //获取更多内存并拷贝现有元素
    std::string *elements;      //指向数组首元素的指针
    std::string *first_free;    //指向数组第一个空闲位置的指针
    std::string *cap;           //指向数组尾后位置的指针
};

std::allocator<std::string> StrVec::alloc; 

StrVec::StrVec(std::initializer_list<std::string> il) {
    auto newData = alloc_n_copy(il.begin(), il.end());
    elements = newData.first;
    first_free = cap = newData.second;
}

StrVec::StrVec(StrVec &&rhs) noexcept:
        elements(rhs.elements), first_free(rhs.first_free), cap(rhs.cap) {
    rhs.elements = rhs.cap = rhs.first_free = nullptr;
}

StrVec& StrVec::operator=(StrVec &&rhs) noexcept {
    if (&rhs != this) {     //自赋值检测
        free();
        elements = rhs.elements;
        cap = rhs.cap;
        first_free = rhs.first_free;
        rhs.elements = rhs.cap = rhs.first_free = nullptr;
    }
} 

void StrVec::push_back(const std::string& s){
    chk_n_alloc();
    alloc.construct(first_free++, s);
}

void StrVec::push_back(std::string &&s) {
    chk_n_alloc();
    alloc.construct(first_free++, std::move(s));
}

std::pair<std::string*, std::string*> 
StrVec::alloc_n_copy(const std::string *b, const std::string *e) {
    //分配空间来保存给定范围的元素
    auto data = alloc.allocate(e-b);
    //返回一个pair，包含两个地址
    return {data, std::uninitialized_copy(b, e, data)};
}

void StrVec::free() {
    //elements为空说明区域本身就没分配好，函数什么都不要做
    if (elements) {
        // for (auto p = first_free; p != elements;)
        //     alloc.destroy(--p);
        for_each(elements, first_free, [this](std::string &s){alloc.destroy(&s);});
        alloc.deallocate(elements, cap-elements);
    }
}

StrVec::StrVec(const StrVec &s) {
    auto newData = alloc_n_copy(s.begin(), s.end());
    elements = newData.first;
    first_free = cap = newData.second;
}

StrVec::~StrVec() {
    free();
}

StrVec &StrVec::operator=(const StrVec &s) {
    auto data = alloc_n_copy(s.begin(), s.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
}

void StrVec::reallocate(size_t newSize){
    if (newSize == 0)
        newSize = elements == nullptr ? 1 : size()*2;
    auto first = alloc.allocate(newSize);
    // auto dest = newData;
    // auto elem = elements;
    // for (size_t i = 0; i != size(); ++i)
    //     alloc.construct(dest++, std::move(*elem++));
    auto last = std::uninitialized_copy(
            std::make_move_iterator(begin()), std::make_move_iterator(end()), first);
    free();
    elements = first;
    first_free = last;
    cap = first + newSize;
}

void StrVec::reserve(size_t n) {
    if(n <=  capacity())
        return;
    reallocate(n);
}

void StrVec::resize(size_t ns, const std::string &s) {
    if (ns == size())
        return;
    else if (ns < size()) {
        while (first_free - elements > ns)
            alloc.destroy(--first_free);
    } else {
        reallocate(ns*2);
        for (auto i = size(); i != ns; ++i)
            alloc.construct(first_free++, s);
    }
}

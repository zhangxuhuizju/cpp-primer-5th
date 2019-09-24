#include <memory>
#include <string>
#include <vector>
#include <algorithm>

class StrVec{
public:
    StrVec():
        elements(nullptr), first_free(nullptr),cap(nullptr){}
    StrVec(const StrVec&);                  //拷贝构造函数
    StrVec& operator=(const StrVec&);       //拷贝赋值运算符
    ~StrVec();                              //析构函数
    void push_back(const std::string&);     //拷贝元素
    size_t size() const {return first_free-elements;}
    size_t capacity() const {return cap-elements;}
    std::string *begin() const{return elements;}
    std::string *end() const{return first_free;}
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
    void reallocate();          //获取更多内存并拷贝现有元素
    std::string *elements;      //指向数组首元素的指针
    std::string *first_free;    //指向数组第一个空闲位置的指针
    std::string *cap;           //指向数组尾后位置的指针
};

void StrVec::push_back(const std::string& s){
    chk_n_alloc();
    alloc.construct(first_free++, s);
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
        for (auto p = first_free; p != elements;)
            alloc.destroy(--p);
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


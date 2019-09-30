#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <iterator>

template<typename T> class Vec;  //注意先声明！
template <typename T> bool operator==(const Vec<T>&, const Vec<T>&);
template <typename T> bool operator!=(const Vec<T>&, const Vec<T>&);

template<typename T>
class Vec {
    friend bool operator==<T>(const Vec<T>&, const Vec<T>&);
    friend bool operator!=<T>(const Vec<T>&, const Vec<T>&);
public:
    Vec():
        elements(nullptr), first_free(nullptr), cap(nullptr){}
    Vec(std::initializer_list<T>);
    Vec(const Vec&);                    //拷贝构造函数
    Vec(Vec&&) noexcept;                //移动构造函数
    Vec& operator=(const Vec&);         //拷贝赋值运算符
    Vec& operator=(Vec&&) noexcept;     //移动赋值运算符
    ~Vec();
    void push_back(const T&);
    void push_back(T&&);
    std::size_t size() const {return first_free-elements;}
    std::size_t capacity() const {return cap-elements;}
    T *begin() const{return elements;}
    T *end() const{return first_free;}
    void reserve(size_t n);
    void resize(size_t s, const T& t= T());
    T& operator[](const size_t n);
    const T& operator[](const size_t n) const;

private:
    static std::allocator<T> alloc;     //allocate elements
    //被添加元素的函数使用
    void chk_n_alloc() {
        if (size() == capacity())
            reallocate();
    }
    //工具函数，被拷贝构造函数、赋值运算符和析构函数使用
    std::pair<T*, T*> alloc_n_copy(const T*, const T*);
    void free();
    void reallocate(size_t newSize = 0);
    T *elements;            //指向数组首元素的指针
    T *first_free;          //指向数组第一个空闲位置的指针
    T *cap;                 //指向数组尾后位置的指针
};

template<typename T>std::allocator<T> Vec<T>::alloc; 

template<typename T>Vec<T>::Vec(std::initializer_list<T> il) {
    auto newData = alloc_n_copy(il.begin(), il.end());
    elements = newData.first;
    first_free = cap = newData.second;
}

template<typename T>Vec<T>::Vec(Vec &&rhs) noexcept:
    elements(rhs.elements), first_free(rhs.first_free), cap(rhs.cap) {
    rhs.elements = rhs.cap = rhs.first_free = nullptr;
}

template<typename T>
Vec<T>&  Vec<T>::operator=(Vec &&rhs) noexcept {
    if (&rhs != this) {     //自赋值检测
        free();
        elements = rhs.elements;
        cap = rhs.cap;
        first_free = rhs.first_free;
        rhs.elements = rhs.cap = rhs.first_free = nullptr;
    }
} 

template<typename T>
void Vec<T>::push_back(const T& s){
    chk_n_alloc();
    alloc.construct(first_free++, s);
}

template<typename T>
void Vec<T>::push_back(T &&s) {
    chk_n_alloc();
    alloc.construct(first_free++, move(s));
}

template<typename T> std::pair<T*, T*> 
Vec<T>::alloc_n_copy(const T *b,const T *e) {
    //分配空间来保存给定范围的元素
    auto data = alloc.allocate(e-b);
    //返回一个pair，包含两个地址
    return {data, std::uninitialized_copy(b, e, data)};
}

template<typename T>
void Vec<T>::free() {
    //elements为空说明区域本身就没分配好，函数什么都不要做
    if (elements) {
        // for (auto p = first_free; p != elements;)
        //     alloc.destroy(--p);
        for_each(elements, first_free, [this](T &s){alloc.destroy(&s);});
        alloc.deallocate(elements, cap-elements);
    }
}

template<typename T>
Vec<T>::Vec(const Vec &s) {
    auto newData = alloc_n_copy(s.begin(), s.end());
    elements = newData.first;
    first_free = cap = newData.second;
}

template<typename T>
Vec<T>::~Vec() {
    free();
}

template<typename T>
Vec<T>& Vec<T>::operator=(const Vec &s) {
    auto data = alloc_n_copy(s.begin(), s.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
}

template<typename T>
void Vec<T>::reallocate(size_t newSize){
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

template<typename T>
void Vec<T>::reserve(size_t n) {
    if(n <=  capacity())
        return;
    reallocate(n);
}

template<typename T>
void Vec<T>::resize(size_t ns, const T &s) {
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

template<typename T>
bool operator==(const Vec<T>& lhs, const Vec<T>& rhs) {
    if (lhs.size() != rhs.size())
        return false;
    for (size_t i = 0; i != lhs.size(); ++i)
        if (*(lhs.elements+i) != *(rhs.elements+i))
            return false;
    return true;
}

template<typename T>
bool operator!=(const Vec<T>& lhs, const Vec<T>& rhs) {
    return !(lhs == rhs);
}

template<typename T>
T& Vec<T>::operator[](const size_t n) {
    if (n >= size())
        throw std::runtime_error("index out of range!");
    return elements[n];
}

template<typename T>
const T& Vec<T>::operator[](const size_t n) const {
    if (n >= size())
        throw std::runtime_error("index out of range!");
    return elements[n];
}

int main(int argc, char const *argv[])
{
    Vec<std::string> v = {"s", "a"};
    std::cout << v[1] << std::endl;
    v.push_back("sss");
    Vec<std::string> vv = v;
    std::cout << vv[2] << std::endl;
    vv.resize(10);
    std::cout << vv[9] << std::endl;
    return 0;
}

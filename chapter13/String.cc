#include <algorithm>
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <vector>
#include "String.h"

std::pair<char*, char*> 
String::alloc_n_copy(const char* b, const char* e) {
    auto str = alloc.allocate(e-b);
    return {str, std::uninitialized_copy(b, e, str)};
}

void String::range_initializer(const char* b, const char* e) {
    auto str = alloc_n_copy(b, e);
    elements = str.first;
    ends = str.second;
}

String::String(const char* s) {
    size_t len = strlen(s);
    //最后的‘\0’也分配空间
    range_initializer(s, s+len+1);
    //std::cout << "const char*" << std::endl;
}

String::String(const String& s) {
    range_initializer(s.elements, s.ends);
    //std::cout << "const string&s" << std::endl;
}

void String::free() {
    if (elements) {
        std::for_each(elements, ends, [this](char& c){alloc.destroy(&c);});
        alloc.deallocate(elements, ends-elements);
    }  
}

String::~String() {
    free();
}

String& String::operator=(const String &s) {
    free();
    range_initializer(s.elements, s.ends);
    //std::cout << "operator=" << std::endl;
    return *this;
}

String& String::operator=(String &&s) noexcept {
    if (&s != this) {
        free();
        elements = s.elements;
        ends = s.ends;
        s.elements = s.ends = nullptr;
    }
    return *this;
}


std::ostream & operator << (std::ostream &out,  const String& s) {
    std::for_each(s.elements, s.ends, [&out](char &c){out<<c;});
    //out << "output:";
    return out;
}

bool operator==(const String& lhs, const String& rhs) {
    size_t llen = lhs.size();
    size_t rlen = rhs.size();
    if (llen != rlen)
        return false;
    for (auto i = 0; i < llen; ++i)
        if (*(lhs.elements+i) != *(rhs.elements+i))
            return false;
    return true;
}

bool operator!=(const String& lhs, const String& rhs) {
    return !(lhs == rhs);
}

bool operator<(const String& lhs, const String& rhs) {
    size_t llen = lhs.size();
    size_t rlen = rhs.size();
    size_t size = llen < rlen ? llen : rlen;
    for (int i = 0; i < size; ++i)
        if (*(lhs.elements+i) != *(rhs.elements+i))
            return *(lhs.elements+i) < *(rhs.elements+i);
    return llen < rlen;
}

char& String::operator[](const size_t n){
    if (n >= size())
        throw std::runtime_error("index out of range!");
    return elements[n];
}

const char& String::operator[](const size_t n) const {
    if (n >= size())
        throw std::runtime_error("index out of range!");
    return elements[n];
}

int main()
{
    char text[] = "world";
 
    String s0;
    String s1("hello");

    String s2(s0);
    
    String s3 = s1;     //初始化的时候是拷贝构造！！！不是赋值运算！！！
    String s4(text);
    s2 = s1;
 
    //std::cout << "-----------------------" << std::endl;
    // std::cout << s1 << std::endl;
    // std::cout << s2 << std::endl;
    // std::cout << s3 << std::endl;
    // std::cout << s4 << std::endl;
    
    std::vector<String> svec;
    svec.push_back(s0);
    svec.push_back(s1);
    svec.push_back(s2);
    svec.push_back(s3);
    svec.push_back(s4);
    svec.push_back("good job");
    
    std::cout << "----------------------" << std::endl;
    // std::cout << s0 << ' ' << s1 << ' ' << s2 << ' ' <<s3 << ' ' << s4 << std::endl;

    for (auto& s : svec) {
        std::cout << s << std::endl;
    }
}
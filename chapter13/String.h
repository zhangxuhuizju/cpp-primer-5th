#ifndef STRINGH
#define STRINGH

#include <memory>
#include <iostream>
#include <algorithm>

class String {
public:
    friend std::ostream& operator << (std::ostream &out,  const String& s);
     
    String():String(""){}
    String(const char*);
    String(const String&);
    String(String &&s) noexcept:elements(s.elements), ends(s.ends)
            {s.elements = s.ends = nullptr;}
    String& operator=(const String&);
    String& operator=(String &&) noexcept;
    ~String();

private:
    std::pair<char*, char*> alloc_n_copy(const char*, const char*);
    void range_initializer(const char*, const char*);
    void free();

    char* elements;
    char* ends;
    static std::allocator<char> alloc;
};

std::allocator<char> String::alloc;

#endif
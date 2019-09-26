#ifndef STRINGH
#define STRINGH

#include <memory>
#include <iostream>
#include <algorithm>

class String {
public:
    friend std::ostream& operator << (std::ostream &out,  const String& s);
    friend bool operator==(const String&, const String&);
    friend bool operator!=(const String&, const String&);
    friend bool operator<(const String&, const String&);

    String():String(""){}
    String(const char*);
    String(const String&);
    String(String &&s) noexcept:elements(s.elements), ends(s.ends)
            {s.elements = s.ends = nullptr;}
    String& operator=(const String&);
    String& operator=(String &&) noexcept;
    char& operator[](const size_t n);
    const char& operator[](const size_t n) const;
    size_t size() const{return ends-elements;}
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

std::ostream& operator << (std::ostream &out,  const String& s);

bool operator==(const String&, const String&);

bool operator!=(const String&, const String&);

bool operator<(const String&, const String&);

#endif
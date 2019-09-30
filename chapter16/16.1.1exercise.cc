#include <iostream>

template<typename InputIterator, typename T>
InputIterator my_find(const InputIterator& begin, const InputIterator& end, const T& val) {
    auto iter = begin;
    while (iter != end) {
        if (*iter == val)
            return iter;
        ++iter;
    }
    return iter;
}

template<typename T> void my_print(const T& array) {
    for (auto item : array)
        std::cout << item << ' ';
    std::cout << std::endl;
} 

template<typename T, size_t N> T* begin(T(&arr)[N]) {
    return arr;
}

template<typename T, size_t N> T* end(T(&arr)[N]) {
    return arr + N;
}

template<typename T, size_t N> constexpr size_t size(const T(&arr)[N]) {
    return N;
}

int main(int argc, char const *argv[])
{
    int a[] = {1,2,3,54};
    my_print(a);
    std::cout << *begin(a) << ' ' << *(end(a)-1) << ' ' << size(a) << std::endl;
    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class ifthenelse{
public:
    ifthenelse() = default;
    int operator()(bool a, int b, int c) {
        return a ? b : c;
    }
};

class getLine {
public:
    getLine(std::istream &in = std::cin):
        in(in){}
    std::string operator()() {
        std::string s;
        getline(in, s);
        if (in)
            return s;
        else
            return "";
    }
private:
    std::istream &in;
};

class Equal{
public:
    Equal(int value):value(value){}
    bool operator()(int x) {
        return value == x;
    }
private:
    int value;
};

int main(int argc, char const *argv[])
{
    // std::vector<std::string> v;
    // getLine get;
    // v.push_back(get());
    // v.push_back(get());
    // std::cout << v[0] << '\n' << v[1] << std::endl;
    std::vector<int> v{1,2,3,4,2,3,5,2,4,5};
    std::replace_if(v.begin(), v.end(), Equal(2), 222);
    for (auto i : v)
        std::cout << i << ' ';
    std::cout << std::endl;
    return 0;
}

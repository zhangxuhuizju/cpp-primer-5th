#include<iostream>

class DebugDelete {
public:
    DebugDelete(std::ostream &s = std::cerr):os(s){}
    template <typename T> void operator()(T *p) const {
        delete p;
        os << "delete using DebugDelete" << std::endl;
    }
private:
    std::ostream &os;
};

int main(int argc, char const *argv[])
{
    int *a = new int(2);
    DebugDelete()(a);
    char c;
    return 0;
}

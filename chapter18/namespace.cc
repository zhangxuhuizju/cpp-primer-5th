#include <iostream>

namespace mathLib {
    namespace MatrixLib {
        class Int {
        public:
            int num = 10;
            Int(){}
            Int(int num):num(num){}
        };
        Int operator* (const Int& a, const Int& b) {
            return Int();
        }
    }
}

using namespace mathLib::MatrixLib;

int main(int argc, char const *argv[])
{
    Int b(20), c(10);
    Int a = b*c;
    
    return 0;
}

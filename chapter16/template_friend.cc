#include<iostream>

template <typename T> class A;
template <typename T> class B;
template <typename T> class C;
template <typename T> void printAB(const A<T>&, const B<T>&);
template <typename T, typename X> void printAC(A<T> a, C<X> c);
//void printAC(const A&, const C&);

template <typename T> class A {
    friend class C<T>;
    template<typename X> friend class B;
    friend void printAB<T>(const A<T>&, const B<T>&);
    
    template <typename G, typename X> friend void printAC(A<G> a, C<X> c);
    
    int num = 10;
};

template <typename T> class B {
public:
    template<typename G> void print(A<G> a) {
        std::cout << a.num << std::endl;
    }
};

template <typename T> class C {
public:
    template<typename G> void print(A<G> a) {
        std::cout << a.num << std::endl;
    }
};

template <typename T> void printAB(const A<T>& a, const B<T>& b) {
    std::cout << a.num << std::endl;
    std::cout << "printAB" << std::endl;
}

template <typename T, typename X> void printAC(A<T> a, C<X> c) {
    std::cout << a.num << std::endl;
    std::cout << "printAC" << std::endl;
}

int main(int argc, char const *argv[])
{
    A<int> a;
    B<int> b;
    B<double> bb;
    C<int> c;
    C<double> cc;
    printAC(a,c);
    printAC(a,cc);
    printAB(a, b);
    bb.print(a);
    //cc.print(a);
    return 0;
}

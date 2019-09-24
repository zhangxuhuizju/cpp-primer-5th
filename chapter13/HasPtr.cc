#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class HasPtr{
public:
    friend void swap(HasPtr&, HasPtr&);
    friend bool operator<(const HasPtr&, const HasPtr&);
    HasPtr(const string &s = string()):
            ps(new string(s)), i(0), use(new size_t(1)){}
    HasPtr(const HasPtr &p):
            ps(p.ps), i(p.i), use(p.use) {++*use;}
    ~HasPtr();
    HasPtr& operator=(const HasPtr&);
    string getPs(void) {return *ps;}
private:
    string *ps;
    int i;
    size_t *use;
};

void swap(HasPtr& lhs, HasPtr& rhs) {
    std::swap(lhs.ps, rhs.ps);
    std::swap(lhs.i, rhs.i);
    std::swap(lhs.use, rhs.use);
    cout << "using swap" << endl;
}

bool operator<(const HasPtr& lhs, const HasPtr& rhs) {
    return *lhs.ps < *rhs.ps;
}

HasPtr::~HasPtr() {
    if (--*use == 0) {
        delete use;
        delete ps;
    }
}

HasPtr& HasPtr::operator=(const HasPtr& rhs){
    ++*rhs.use;
    if (--*use == 0) {
        delete use;
        delete ps;
    }
    ps = rhs.ps;
    i = rhs.i;
    use = rhs.use;
    return *this;
}

int main(int argc, char const *argv[])
{
    vector<HasPtr> v{string("tobe"), string("ornot"), string("apple")};
    cout << "begin sort" << endl;
    sort(v.begin(), v.end());
    cout << "after sort" << endl;
    for (HasPtr hp : v)
        cout << hp.getPs() << " ";
    cout << endl;
    return 0;
}

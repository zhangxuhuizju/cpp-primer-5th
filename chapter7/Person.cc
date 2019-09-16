#include "Person.h"

Person::Person(istream &is) {
    read(is, *this);
}

istream& read(istream &is, Person &person) {
    // string name, address;
    // is >> name >> address;
    // person.setName(name);
    // person.setAddress(address);
    is >> person.name >> person.address;
    return is;
}

ostream& print(ostream &os, const Person &person) {
    os << person.getName() << " " << person.getAddress();
    return os;
}

int main(int argc, char const *argv[])
{
    Person a = Person(cin);
    print(cout, a);
    return 0;
}

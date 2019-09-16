#ifndef PERSON
#define PERSON

#include <string>
#include <iostream>
using namespace std;

class Person {
public:
    Person() = default;
    Person(const string &name,const string &address):
           name(name), address(address){};
    Person(istream &is);

    string getName() const{
        return this->name;
    }
    string getAddress() const{
        return this->address;
    }

    void setName(string name) {
        this->name = name;
    }

    void setAddress(string address) {
        this->address = address;
    }

private:
    string name = "";
    string address = "";

friend istream& read(istream &, Person &);
// friend ostream& print(ostream &, const Person &);
};

istream& read(istream &, Person &);

ostream& print(ostream &, const Person &);

#endif
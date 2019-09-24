#include<iostream>  
#include<string>  
#include<fstream>
#include<list>
#include<vector> 
#include<map>  
#include<set>
#include<cctype>//ctype无法打开，包含tolower()函数和ispunct函数
#include<algorithm>
#include<utility>
#include<memory>
using namespace std;

class Employee{
public:
    Employee():eName(""), eID(ID){}
    Employee(string& name):eName(name), eID(ID){}
    Employee(const Employee&) = delete;
    Employee& operator=(const Employee &) = delete;
private:
    string eName;
    uint eID;
    static uint ID;
};

uint Employee::ID = 0;
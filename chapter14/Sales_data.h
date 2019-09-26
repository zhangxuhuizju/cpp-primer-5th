#ifndef SALES_DATA
#define SALES_DATA

#include <string>
#include <iostream>
using namespace std;
class Sales_data {
public:
	Sales_data() = default;
    Sales_data(const string &s):bookNo(s){}
    Sales_data(const string &s, unsigned u, double p):
               bookNo(s), units_sold(u), revenue(u*p){}
    Sales_data(istream &is);

    Sales_data& operator+=(const Sales_data &rhs) {
        this->combine(rhs);
        return *this;
    }

    explicit operator string() const{
        return bookNo;
    }

    explicit operator double() const{
        return avg_price();
    }
    
    string isbn() const {
        return bookNo;
    }
    Sales_data& combine(const Sales_data &);
private:
	string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;//类内部的变量成员不允许在定义时初始化，必须使用构造函数
    double avg_price() const;

friend istream &read(istream &, Sales_data &);
friend ostream &print(ostream &, const Sales_data &);
friend Sales_data add(const Sales_data &, const Sales_data &);
friend ostream& operator<<(ostream &, const Sales_data&);
friend Sales_data operator+(const Sales_data&, const Sales_data&);
friend istream& operator>>(istream &, Sales_data &);
};

istream &read(istream &, Sales_data &);

ostream &print(ostream &, const Sales_data &);

Sales_data add(const Sales_data &, const Sales_data &);

ostream& operator<<(ostream &, const Sales_data&);

istream& operator>>(istream &, Sales_data &);

Sales_data operator+(const Sales_data&, const Sales_data&);

#endif
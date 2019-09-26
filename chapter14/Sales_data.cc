#include "Sales_data.h"

Sales_data::Sales_data(istream &is) {
    read(is, *this);
}

inline double Sales_data::avg_price() const {
    if (units_sold)
        return revenue / units_sold;
    else 
        return 0;
}

Sales_data& Sales_data::combine(const Sales_data & rhs) {
    this->units_sold += rhs.units_sold;
    this->revenue += rhs.revenue;
    return *this;
}

istream &read(istream & is, Sales_data &item) {
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = item.units_sold * price;
    return is;
}

ostream &print(ostream & os, const Sales_data & item) {
    os << item.isbn() << " " << item.units_sold << " "
       << item.revenue << " " << item.avg_price();
    return os;
}

Sales_data add(const Sales_data & item1, const Sales_data & item2) {
    Sales_data sum = item1;
    sum.combine(item2);
    return sum;
}

ostream& operator<<(ostream &os, const Sales_data &item) {
    os << item.isbn() << " " << item.units_sold << " "
       << item.revenue << " " << item.avg_price();
    return os;
}

istream& operator>>(istream &is, Sales_data &item) {
    double price;
    is >> item.bookNo >> item.units_sold >> price;
    if (is)
        item.revenue = item.units_sold * price;
    else 
        item = Sales_data();        //判断输入是否失败
    return is;
}

Sales_data operator+(const Sales_data& lhs, const Sales_data& rhs) {
    Sales_data sum = lhs;
    sum += lhs;
    return sum;
}

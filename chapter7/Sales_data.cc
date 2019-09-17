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

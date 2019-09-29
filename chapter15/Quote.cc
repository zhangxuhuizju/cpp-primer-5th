#include "Quote.h"

double print_total(std::ostream &os, const Quote &item, size_t n) {
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn() << " #sold: " << n
       << " total due: " << ret << std::endl;
    return ret;
}

Quote& Quote::operator=(const Quote& quote) {
    this->bookNo = quote.bookNo;
    this->price = quote.price;
    std::cout << "Quote拷贝赋值运算符" << std::endl;
    return *this;
}

Quote& Quote::operator=(Quote &&quote) noexcept{
    if (&quote != this) {
        this->bookNo = std::move(quote.bookNo);
        this->price = std::move(quote.price);
    }
    std::cout << "Quote移动赋值运算符" << std::endl;
    return *this;
}

void Quote::debug(void) const {
    std::cout << "BookNo: " << bookNo << '\n'
              << "Price: " << price << std::endl;
}

void Bulk_quote::debug(void) const {
    Quote::debug();
    std::cout << "Quantity: " << quantity << '\n'
              << "Discount: " << discount << std::endl;
}

Bulk_quote::
Bulk_quote(const std::string& book, double sales_price, 
            std::size_t qty, double disc):
            Disc_quote(book, sales_price, qty, disc){}

double Bulk_quote::net_price(std::size_t n) const {
    if (n >= quantity)
        return n * (1 - discount) * price;
    else
        return n * price;
}

// int main(int argc, char const *argv[])
// {
//     Quote b1("龙族I", 128);  
// 	Bulk_quote b2(std::string("龙族II"), 128.0, 10, 0.3);
	
// 	print_total(std::cout, b1, 10);   
// 	print_total(std::cout, b2, 10);
	
//     std::cout << "----------------------" << std::endl;
// 	b1.debug();
// 	b2.debug();
//     return 0;
// }

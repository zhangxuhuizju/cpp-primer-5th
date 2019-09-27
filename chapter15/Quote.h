#ifndef QUOTE
#define QUOTE

#include <string>
#include <iostream>

class Quote{
public:
    Quote() = default; 
    Quote(const std::string &book, double sales_priice):
            bookNo(book), price(sales_priice){}
    Quote(const Quote& quote):
            bookNo(quote.bookNo), price(quote.price){
        std::cout << "Quote拷贝构造函数" << std::endl;
    }
    Quote(Quote &&quote) noexcept:
        bookNo(std::move(quote.bookNo)), price(std::move(quote.price)) {
        std::cout << "Quote移动构造函数" << std::endl;
    }
    Quote& operator=(const Quote&);
    Quote& operator=(Quote &&quote) noexcept;
    std::string isbn() const {return bookNo;}
    virtual double net_price(std::size_t n) const {
        return n*price;
    }
    virtual void debug(void) const;
    virtual ~Quote() = default;
private:
    std::string bookNo;
protected:
    double price = 0.0;
};

class Disc_quote : public Quote {
public:
    Disc_quote();
    Disc_quote(const std::string& book, double price,
               std::size_t qty, double disc):
               Quote(book, price),
               quantity(qty), discount(disc){}
    double net_price(std::size_t n) const = 0;
    virtual ~Disc_quote() override = default;
protected:
    size_t quantity = 0;        //折扣适用的购买量
    double discount = 0.0;      //表示这口的小数值
};

class Bulk_quote : public Disc_quote {
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string&, double, std::size_t, double);
    double net_price(std::size_t n) const override;
    void debug(void) const override;
    ~Bulk_quote() override = default;
};

double print_total(std::ostream &os, const Quote &item, size_t n) {
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn() << " #sold: " << n
       << " total due: " << ret << std::endl;
    return ret;
}
#endif
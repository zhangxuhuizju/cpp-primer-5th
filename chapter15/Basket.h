#ifndef BASKETH
#define BASKETH

#include <memory>
#include "Quote.h"
#include <set>

class Basket {
public:
    void add_item(const Quote &sale){
        items.insert(std::shared_ptr<Quote>(sale.clone()));
    }
    void add_item(Quote &&sale){
        items.insert(std::shared_ptr<Quote>(std::move(sale).clone()));
    }
    //打印每本数的总价和购物篮中所有书的总价
    double total_receipt(std::ostream&) const;
private:
    static bool compare(const std::shared_ptr<Quote> &lhs,
                        const std::shared_ptr<Quote> &rhs) {
        return lhs->isbn() < rhs->isbn();
    }
    std::multiset<std::shared_ptr<Quote>, decltype(compare)*>
                    items{compare};
};

#endif
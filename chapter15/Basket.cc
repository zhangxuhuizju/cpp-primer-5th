#include "Basket.h"

double Basket::total_receipt(std::ostream& os) const {
    double sum = 0.0;
    for(auto iter = items.cbegin(); 
        iter != items.cend();
        iter = items.upper_bound(*iter)) {
        sum += print_total(os, **iter, items.count(*iter));
    }
    os << "Total Sale: " << sum << std::endl;
    return sum;
}

int main(int argc, char const *argv[])
{
    Bulk_quote b2(std::string("II"), 128.0, 10, 0.3);
	Bulk_quote b3(std::string("II"), 128.0, 10, 0.3);
    Quote b1("I", 128);  
	
    Basket basket;
    basket.add_item(b3);
    basket.add_item(b2);
    basket.add_item(b2);
    basket.add_item(b2);
    basket.add_item(b2);
    basket.add_item(b2);
    basket.add_item(b2);
    basket.add_item(b2);
    basket.add_item(b2);
    basket.add_item(b2);
    basket.add_item(b1);
    basket.total_receipt(std::cout);
    return 0;
}

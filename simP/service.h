#include <iostream>
#include "customer.h"
#include "seller.h"

class Service: public Customer {
public:
    std::vector<Customer> customerList;
    void delName(std::string name);
    int check_Name(string name);
    void getPoint(std::string name, int amount);
    void usePoint(std::string name);
    void addPoint(int amount, int idx_at);
    void subPoint(int amount, int idx_at);
    void useCard();
    void order(seller admin);
    void save_customerList();
    void load_customerList();
};
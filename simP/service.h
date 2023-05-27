#include <string>
#include <vector>

class Service: public Customer {
public:
    std::vector<Customer> customerList;
    void delName(std::string name);
    void getPoint(std::string name, int amount);
    void usePoint(std::string name);
    void useCard();
    void order(std::string name);
};
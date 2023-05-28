#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class product{
    string p_name; // name of product
    int stock;          // stock of product. The number of basic stocks is five
public:
    product(string name);  // 
    void stock_fill();          // filling stock up to five
    bool stock_minus(int num);  // stock minus num. if num > stock return false
    void stock_plus(int num);   // stock plus num. this function is used when refund is made
    void change_name(std::string new_name);     // change product name.
    string get_name();                     // return product name.
    int get_stock();                       // return product stock(remain).
};

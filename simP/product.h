#define _CRT_SECURE_NO_WARNINGS
#include <iostream>


class product{
    std::string p_name;
    int stock;
public:
    void stock_fill();
    void stock_minus(int num);
    void change_name(std::string new_name);
    std::string get_name();
    int get_stock();
};

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <map>
#include <ctime>
#include <chrono>
#include <fstream>
#include <string>
#include "product.h"
using namespace std;

// load시, 기존에 있던 data를 다 날리고 새로 dictionary를 만들기

class seller{
    std::map<std::string, int> product_income_pair;
    std::map<int, int> day_income_pair;
    std::string password;
    int cur_date;
    int income;
public:
    product* init_product_info();
    void day_plus_one();
    void clear_seller_income();
    void set_day_today();
    void init_product_income_map();
    void refund(string name, int n, product *p);
    // refund 의 경우는, 일단은 단순하게 구현하고, 영수증을 구현할 여력이 되면, 영수증을
    // 리스트나 뭐 아무거나로 구현해서 영수증 일련번호를 받아서 전체 환불을 진행하는 식으로 해볼까
    seller();
    bool check_Password(std::string pass_input);
    void end_Day(product* p);
    void show_Data();
    void payment_complete(std::string name, int count, product* p);
    int get_price(std::string name);

    void init_csv();
    void load_product_csv();
    void load_date_csv();
    void save_product_csv();
    void save_date_csv();
};
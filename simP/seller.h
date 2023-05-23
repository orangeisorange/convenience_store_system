#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <map>
#include <ctime>
#include <chrono>
#include <fstream>
#include <string>
#include "product.h"


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
    seller();
    // end_Day가 실행되면, 날짜가 다음날로 바뀜과 동시에, csv 파일 생성 또는 최신화.
    bool check_Password(std::string pass_input);
    void end_Day();
    void show_Data();
    void payment_complete(std::string name, int count, product* p);
    int get_price(std::string name);

    void init_csv();
    void load_product_csv();
    void load_date_csv();
    void save_product_csv();
    void save_date_csv();
};
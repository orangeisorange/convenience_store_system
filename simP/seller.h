#define _CRT_SECURE_NO_WARNINGS

#include "product.h"
#include <iostream>
#include <map>
#include <ctime>
#include <chrono>
#include <fstream>
#include <string>
using namespace std;

extern map<int, int> day_income_pair;
extern map<std::string, int> product_income_pair;

class seller{
//    std::map<int, int> day_income_pair;             // Used when using csv file.  <day(ex.230528), that day's whole income>
    std::string password;                           // seller mode is basically restricted. password is 1q2we3e4r!
    int cur_date;                                   // Date on the system. It might not be today.
    int income;                                     // daily whole income
    product* products;                              // product pointer. there are 5 product in this convenience store
public:
//    std::map<std::string, int> product_income_pair; // Used when using csv file.  <product_name, product's whole income>
    product* init_product_info();                    // init product array and return address
//    void init_product_income_map();                 // init product_map
    seller();                                       // seller init

    void day_plus_one();                            // when end of day, this is used. cur_date + 1
    void clear_seller_income();                     // when end of day, this is used. income become 0
    void set_day_today();                           // make cur_date become today.
    product* get_product();

    void refund(string name, int n, product *p);
    // refund 의 경우는, 일단은 단순하게 구현하고, 영수증을 구현할 여력이 되면, 영수증을
    // 리스트나 뭐 아무거나로 구현해서 영수증 일련번호를 받아서 전체 환불을 진행하는 식으로 해볼까

    bool check_Password(std::string pass_input);    // password checking. if password is correct, return true. else false.
    void end_Day(product* p);                       // When end_Day runs, the date changes to the next day, and the csv file is updated.
    void show_Data();                               // show all the product-income , date-income data.
    void show_product();
    void payment_complete(std::string name, int count, product* p, map<string, int>& sel_map, map<int, int>& pro_map); // Used when customer paying the product. product stock - count. this->income + product's
    int get_price(std::string name);                // return product's price. If the name of the product is nowhere to be found return 0

/* below this line is all about csv management. These are used when end of day or save or load the data*/
    void init_csv();
    void load_product_csv();
    void load_date_csv();
    void save_product_csv();
    void save_date_csv();
};
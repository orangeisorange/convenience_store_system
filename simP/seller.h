#define _CRT_SECURE_NO_WARNINGS

#include "product.h"
#include <iostream>
#include <map>
#include <ctime>
#include <chrono>
#include <fstream>
#include <string>
using namespace std;

// 전역변수 들여오기
extern map<int, int> day_income_pair;
extern map<std::string, int> product_income_pair;
extern map<int, product*> receipt;
extern int cur_day_receipt;
extern product receipt_product[5];
extern void refresh_receipt_product(product* p);


class seller {
    std::string password;                           // seller mode is basically restricted. password is 1q2we3e4r!
    int cur_date;                                   // Date on the system. It might not be today.
    int income;                                     // daily whole income
    product* products;                              // product pointer. there are 5 product in this convenience store
public:
    //    std::map<std::string, int> product_income_pair; // Used when using csv file.  <product_name, product's whole income>
    product* init_product_info();                    // init product array and return address
    //    void init_product_income_map();                 // init product_map
    seller();                                       // seller init
    int get_income();                               // give income
    int get_cur_date();                             // give cur_date
    void day_plus_one();                            // when end of day, this is used. cur_date + 1
    void clear_seller_income();                     // when end of day, this is used. income become 0
    void set_day_today();                           // make cur_date become today.
    product* get_product();                         // seller가 가진 product의 주소를 반환해줌

    void refund(product* p);                        // 사용자에게서 영수증 번호를 받아서 내역을 보여준 뒤, 환불

    bool check_Password(std::string pass_input);    // password checking. if password is correct, return true. else false.
    void end_Day(product* p);                       // When end_Day runs, the date changes to the next day, and the csv file is updated.
    void show_Data();                               // show all the product-income , date-income data.
    void show_product();                            // 재고 보여줄 때 사용
    void show_product(product* p);                  // 재고 이외의 다른 product형 변수를 보여줄 때 사용
    void payment_complete(std::string name, int count, product* p, map<string, int>& sel_map); // Used when customer paying the product. product stock - count. this->income + product's
    int get_price(std::string name);                // return product's price. If the name of the product is nowhere to be found return 0

    // 영수증 관련 함수.
    void load_receipt();
    void save_receipt();
    void show_all_receipt();

    /* below this line is all about csv management. These are used when end of day or save or load the data*/
    void init_csv();
    void load_product_csv();
    void load_date_csv();
    void save_product_csv();
    void save_date_csv();
};
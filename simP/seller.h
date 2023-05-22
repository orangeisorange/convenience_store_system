#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <map>
#include <ctime>
#include <chrono>

// 재고 정리하는 함수 만들어야 함. _ 따로 클래스를 만드는 것에 대해서 고려해 볼것.
// load시, 기존에 있던 data를 다 날리고 새로 dictionary를 만들기
class csv_control{
public:
    static void load_product_csv();
    static void load_date_csv();
    static void save_product_csv();
    static void save_date_csv();
};

class seller{
    std::map<std::string, int> product_income_pair;
    std::map<int, int> day_income_pair;
    std::string password;
    int cur_date;
    int income;
public:
    void clear_seller_income();
    void set_day_today();
    void init_product_income_map();
    seller();
    // end_Day가 실행되면, 날짜가 다음날로 바뀜과 동시에, csv 파일 생성 또는 최신화.
    bool check_Password(std::string pass_input);
    void end_Day();
    void show_Data();
};
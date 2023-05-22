#include "seller.h"
using namespace std;

void seller::set_day_today()
{
    chrono::system_clock::time_point now = chrono::system_clock::now();
    time_t curtime = chrono::system_clock::to_time_t(now);
    tm* localT = localtime(&curtime);

    int Date = (localT->tm_year % 100) * 10000 + (localT->tm_mon + 1) * 100 + localT->tm_mday;
    this->cur_date = Date;
}

seller::seller() {
        init_product_income_map();
        set_day_today();
        this->income = 0;
        this->password = "1q2we3e4r!";
}

bool seller::check_Password(string pass_input) {
    if (this->password == pass_input) return true;
    else return false;
}

void seller::init_product_income_map()
{
    product_income_pair.insert(make_pair("과자", 0));
    product_income_pair.insert(make_pair("삼각김밥", 0));
    product_income_pair.insert(make_pair("커피", 0));
    product_income_pair.insert(make_pair("담배", 0));
    product_income_pair.insert(make_pair("빵", 0));
}

void seller::clear_seller_income() { this->income = 0; }

void seller::day_plus_one() {
    int year = this->cur_date / 10000;
    int month = (this->cur_date % 10000) / 100;
    int day = this->cur_date % 100;
    
    int month_D[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        month_D[1] = 29;
    day += 1;

    if (day > month_D[month - 1]) {
        day = 1; month += 1;
        if (month > 12)
        {
            month = 1; year += 1;
        }
    }
    this->cur_date = year * 10000 + month * 100 + day;
}

void seller::end_Day()
{
    day_income_pair.insert(make_pair(this->cur_date, this->income));
    cout << "다음 날로 변경합니다. ";
    day_plus_one();
}

void seller::show_Data() {
    for (const auto& product : product_income_pair) {
        cout << "상품 명 : " << product.first << "의 매출은 " << product.second * get_price(product.first) << "원" << endl;
    }
    cout << endl << endl;
    for (const auto& day : day_income_pair) {
        cout << day.first << " : " << day.second << "원" << endl;
    }
}

// 결제 완료 되었을 경우, 이 함수 호출. 인자는 상품명, 상품 갯수
void seller::payment_complete(string name, int count)
{
    for (auto& product : product_income_pair) {
        if (product.first == name) {
            product.second += count;
            this->income += count * get_price(name);
        }
    }
}

int seller::get_price(string name)
{
    if (name == "과자")
        return 2500;
    else if (name == "삼각김밥")
        return 1500;
    else if (name == "커피")
        return 2000;
    else if (name == "담배")
        return 4500;
    else if (name == "빵")
        return 3000;
    else
        return 0;
}

void seller::load_product_csv()
{
}

void seller::load_date_csv()
{
    int date;
    int income;
    string test;
    fstream fs;
    fs.open("test.csv", ios::in);
    if (!fs) {
        cout << "" << " 열기 오류" << endl;
    }

    while (!fs.eof()) {
        getline(fs, test, ',');
        
    }
}

void seller::save_product_csv()
{
}

void seller::save_date_csv()
{
}

#include "seller.h"

void seller::set_day_today()
{
    chrono::system_clock::time_point now = chrono::system_clock::now();
    time_t curtime = chrono::system_clock::to_time_t(now);
    tm* localT = localtime(&curtime);

    int Date = (localT->tm_year % 100) * 10000 + (localT->tm_mon + 1) * 100 + localT->tm_mday;
    this->cur_date = Date;
}

product* seller::get_product()
{
    return this->products;
}

seller::seller() {
    set_day_today();
    this->income = 0;
    this->password = "1q2w3e4r!";
    this->products = init_product_info();
    cur_day_receipt = cur_date * 1000 + 1;
}

int seller::get_income()
{
    return income;
}

int seller::get_cur_date()
{
    return cur_date;
}

bool seller::check_Password(string pass_input) {
    if (this->password == pass_input) return true;
    else return false;
}

void seller::refund(string name, int n, product* p)
{
    cout << "환불하실 물품이 있는 영수증의 번호를 입력해 주세요." << endl;
    int tmp_receipt_num;
    cin >> tmp_receipt_num;
    if (receipt.count(tmp_receipt_num) == 0)
    {
        cout << "입력한 영수증의 번호가 존재하지 않습니다!" << endl;
        return;
    }
    show_product(receipt[tmp_receipt_num]);
    cout << "전부 환불하시겠습니까? (Y/N) >> ";
    char Y_N;
    cin >> Y_N;
    if (Y_N == 'Y')
    {
        for (int i = 0; i < 5; i++)
        {
            product_income_pair[receipt[tmp_receipt_num][i].get_name()] -= receipt[tmp_receipt_num][i].get_stock();
            day_income_pair[tmp_receipt_num/1000] -= receipt[tmp_receipt_num][i].get_stock()* get_price(receipt[tmp_receipt_num][i].get_name());
        }
        receipt.erase(tmp_receipt_num);
        return;
    }
    while (1) {
        cout << "환불할 물품을 알려주세요 >>";
        string tmp_product;
        cin >> tmp_product;
        cout << "환불할 갯수를 알려주세요 >>";
        int count;
        cin >> count;
        for (int i = 0; i < 5; i++)
        {
            if (tmp_product == receipt[tmp_receipt_num][i].get_name())
            {
                receipt[tmp_receipt_num][i].stock_minus(count);
                product_income_pair[tmp_product] -= count;
                day_income_pair[tmp_receipt_num / 1000] -= count * get_price(receipt[tmp_receipt_num][i].get_name());
            }
        }
    }

}

void seller::clear_seller_income() { this->income = 0; }

product * seller::init_product_info()
{
    product* p = new product[5]{product("과자"), product("삼각김밥"), product("커피"),product("담배"), product("빵")};
    return p;
}

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

// end_Day가 실행되면, 날짜가 다음날로 바뀜과 동시에, csv 파일 생성 또는 최신화.
void seller::end_Day(product *p)
{
    cout << "다음 날로 변경합니다. ";
    for (int i = 0; i < 5; i++)
    {
        p[i].stock_fill();
    }
    day_plus_one();
    day_income_pair.insert(make_pair(get_cur_date(), get_income()));
    cur_day_receipt = cur_date * 1000 + 1;
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

void seller::show_product()
{
    cout.setf(ios::left);
    cout.width(12);
    cout << "상품명";
    cout.width(12);
    cout << "현재 재고" << endl;
    for (int i = 0; i < 5; i++)
    {
        cout.width(12);
        cout << this->products[i].get_name();
        cout.width(12);
        cout << this->products[i].get_stock() << endl;
    }
}

void seller::show_product(product *p)
{
    cout.setf(ios::left);
    cout.width(12);
    cout << "상품명";
    cout.width(12);
    cout << "주문 했던 갯수" << endl;
    for (int i = 0; i < 5; i++)
    {
        cout.width(12);
        cout << p[i].get_name();
        cout.width(12);
        cout << p[i].get_stock() << endl;
    }
}

// 결제 완료 되었을 경우, 이 함수 호출. 인자는 상품명, 상품 갯수
// 수정 필요. 실제로 값이 바뀌지가 않음.
void seller::payment_complete(std::string name, int count, product* p, map<string, int> &sel_map, map<int, int> &pro_map)
{
    for (int i = 0; i < 5; i++) 
        if (p[i].get_name() == name) {
            p[i].stock_minus(count);
            income += this->get_price(p[i].get_name()) * count;
        }
    sel_map[name] = count;
    pro_map[cur_date] = income;
    receipt.insert(make_pair(cur_day_receipt, receipt_product));
    cur_day_receipt += 1;
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

void seller::init_csv()
{
    // 파일이 없다면 파일 생성
    ofstream fs("product_income.csv");
    ofstream fs1("date_income.csv");
    ofstream fs2("receipt.txt");
    fs.close();
    fs1.close();
    fs2.close();
}

void seller::load_product_csv()
{
    string name;
    int income;
    string test;
    fstream fs("product_income.csv", ios::in);
    if (!fs) {
        cout << "" << " 열기 오류" << endl;
    }
    product_income_pair.clear();
    while (!fs.eof()) {
        getline(fs, test, ',');
        name = test;
        getline(fs, test, ',');
        income = stoi(test);
        product_income_pair.insert(make_pair(name, income));
    }
}

// 경고, 현재까지의 매출을 csv 파일로 미리 save 하지 않은 경우, 입력되었던 매출이 다 날아감
void seller::load_date_csv()
{
    int date;
    int income;
    string tmp;
    fstream fs("date_income.csv", ios::in);
    if (!fs) {
        cout << "" << " 열기 오류" << endl;
    }
    day_income_pair.clear();
    while (!fs.eof()) {
        getline(fs, tmp, ',');
        date = stoi(tmp);
        getline(fs, tmp, ',');
        income = stoi(tmp);
        day_income_pair.insert(make_pair(date, income));
    }
}


void seller::save_product_csv()
{
    ofstream fs("product_income.csv", ios::app || ios::out);
    for (auto& product : product_income_pair)
    {
        fs << product.first << ',' << product.second << '\n';
    }
}

void seller::save_date_csv()
{
    ofstream fs("date_income.csv", ios::app || ios::out);
    for (auto& day : day_income_pair)
    {
        fs << day.first << ',' << day.second << '\n';
    }
}

void seller::load_receipt()
{
    string tmp;
    int receipt_day_num;
    int tmp_count;
    product p[5];
    fstream fs("receipt.txt", ios::in);
    if (!fs) {
        cout << "" << " 열기 오류" << endl;
    }
    receipt.clear();
    while (!fs.eof()) {
        refresh_receipt_product(p);
        getline(fs, tmp, ',');
        receipt_day_num = stoi(tmp);
        for (int i = 0; i < 5; i++)
        {
            getline(fs, tmp, ',');
            tmp_count = stoi(tmp);
            p[i].stock_plus(tmp_count);
        }
    receipt.insert(make_pair(receipt_day_num, p));

    }
}

void seller::save_receipt()
{
    ofstream fs("receipt.txt", ios::app || ios::out);
    for (auto& rct : receipt)
    {
        fs << rct.first << ',';
        for (int i = 0; i < 5; i++)
        {
            fs << rct.second[i].get_stock() << ',';
        }
        fs << '\n';
    }
}

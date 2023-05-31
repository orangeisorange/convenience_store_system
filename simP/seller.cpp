#include "seller.h"



// cur_date에 chrono 헤더파일등등을 통해서 YYMMDD 형식으로 변환한 오늘 날짜의 int 값을 넣어주는 함수
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
    this->password = "1q2w3e4r!";       // seller 모드 비밀번호
    this->products = init_product_info();
    cur_day_receipt = cur_date * 1000 + 1;  // 형식이 ex)2305310001 이라서 이런 형식으로 제작.
    // 하루에 영수증이 999개를 넘지 않는다고 가정하였음.
}

int seller::get_income()
{
    return income;
}

int seller::get_cur_date()
{
    return cur_date;
}

// seller 모드에 진입할 때 암호 체크
bool seller::check_Password(string pass_input) {
    if (this->password == pass_input) return true;
    else return false;
}

void seller::refund(product* p)
{
    cout << "환불하실 물품이 있는 영수증의 번호를 입력해 주세요." << endl;
    int tmp_receipt_num;
    cin >> tmp_receipt_num;
    // 입력한 영수증 번호가 receipt map 상에 한개도 없다면 실행됨
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
            day_income_pair[tmp_receipt_num / 1000] -= receipt[tmp_receipt_num][i].get_stock() * get_price(receipt[tmp_receipt_num][i].get_name());
        }
        receipt.erase(tmp_receipt_num);
        return;
    }
    // 전부 환불하지 않는 경우
    while (1) {
        cout << "환불할 물품을 알려주세요 >>";
        string tmp_product;
        cin >> tmp_product;
        cout << "환불할 갯수를 알려주세요 >>";
        int isthere;
        int count;
        cin >> count;
        // 환불할 물품의 이름과 갯수를 receipt map과 비교하여 환불한 만큼 삭제 + product_income_pair 맵과 day_income_pair 맵에서도 매출 삭제
        for (int i = 0; i < 5; i++)
        {
            if (tmp_product == receipt[tmp_receipt_num][i].get_name())
            {
                receipt[tmp_receipt_num][i].stock_minus(count);
                product_income_pair[tmp_product] -= count;
                day_income_pair[tmp_receipt_num / 1000] -= count * get_price(receipt[tmp_receipt_num][i].get_name());
                isthere = 1;
            }
        }
        if (isthere == 0) {
            cout << "환불할 물품의 이름이 잘못 입력되었습니다." << endl;
            continue;
        }
        else {
            cout << "환불이 완료되었습니다. 더 환불할 것이 있으신가요? (y/n)" << endl;
            char choice;
            cin >> choice;
            if (choice == 'y')
                continue;
            else
                break;
        }
    }

}

void seller::clear_seller_income() { this->income = 0; }

product* seller::init_product_info()
{
    product* p = new product[5]{ product("과자"), product("삼각김밥"), product("커피"),product("담배"), product("빵") };
    return p;
}

// 윤년과 각 달마다 날짜가 다른것을 고려한 다음날로 넘어가주는 함수.
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
void seller::end_Day(product* p)
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

// 저장되있는 매출을 보여줌(상품마다 와 날짜마다로 구분하였음)
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

void seller::show_product(product* p)
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

// 결제가 완료되었을 때, seller의 income에 더해줘서 전체 매출을 계산할 수 있게 하며,
// product_income_pair 맵의 상품별 매출을 최신화 해줌.
void seller::payment_complete(string name, int count, product* p, map<string, int>& pro_map)
{
    for (int i = 0; i < 5; i++) {
        if (p[i].get_name() == name) {
            p[i].stock_minus(count);
            income += (this->get_price(p[i].get_name()) * count);
        }
    }
    pro_map[name] += count;
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

// 처음프로그램 구동시, 파일이 프로젝트 안에 존재하지 않는다면 파일을 생성해주는 함수.
void seller::init_csv()
{
    // 파일이 없다면 파일 생성
    fstream fs("product_income.csv", ios::in);
    if (!fs) {
        ofstream fs("product_income.csv", ios::out);
    }
    fstream fs1("date_income.csv", ios::in);
    if (!fs1) {
        ofstream fs1("date_income.csv", ios::out);
    }
    fstream fs2("receipt.txt", ios::in);
    if (!fs2) {
        ofstream fs2("receipt.txt", ios::out);
    }
    fstream fs3("customerList.txt", ios::in);
    if (!fs3) {
        ofstream fs3("customerList.txt", ios::out);
    }
    fs.close();
    fs1.close();
    fs2.close();
    fs3.close();
}

void seller::load_product_csv()
{
    string name;
    int income1;
    string test;
    fstream fs("product_income.csv", ios::in);
    if (!fs) {
        cout << "" << " 열기 오류" << endl;
    }
    product_income_pair.clear();
    while (getline(fs, test, ',')) {
        name = test;
        getline(fs, test, ',');
        income1 = stoi(test);
        product_income_pair.insert(make_pair(name, income1));
    }
}

// 경고, 현재까지의 매출을 csv 파일로 미리 save 하지 않은 경우, 입력되었던 매출이 다 날아감
void seller::load_date_csv()
{
    int date;
    int income1;
    string tmp;
    fstream fs("date_income.csv", ios::in);
    if (!fs) {
        cout << "" << " 열기 오류" << endl;
    }
    day_income_pair.clear();
    while (getline(fs, tmp, ',')) {
        date = stoi(tmp);
        getline(fs, tmp, ',');
        income1 = stoi(tmp);
        day_income_pair.insert(make_pair(date, income1));
    }
}


void seller::save_product_csv()
{
    ofstream fs("product_income.csv", ios::out);
    for (auto& product : product_income_pair)
    {
        fs << product.first << ',' << product.second << '\n';
    }
}

void seller::save_date_csv()
{
    ofstream fs("date_income.csv", ios::out);
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
    product* p;
    p = new product[5];
    fstream fs("receipt.txt", ios::in);
    if (!fs) {
        cout << "" << " 열기 오류" << endl;
    }
    receipt.clear();
    while (getline(fs, tmp, ',')) {
        p->refresh_receipt_product(p);
        receipt_day_num = stoi(tmp);
        if ( receipt_day_num == 0) break;
        for (int i = 0; i < 5; i++)
        {
            getline(fs, tmp, ',');
            tmp_count = stoi(tmp);
            p[i].stock_plus(tmp_count);
        }

        receipt.insert(make_pair(receipt_day_num, p));
        if(cur_day_receipt < receipt_day_num)
            cur_day_receipt = receipt_day_num + 1;
    }
}

void seller::save_receipt()
{
    ofstream fs("receipt.txt", ios::out);
    for (auto& rct : receipt)
    {
        fs << rct.first << ',';
        for (int i = 0; i < 5; i++)
        {
            fs << rct.second[i].get_stock();
            if (i != 4) fs << ',';
        }
        fs << '\n';
    }
}

// receipt 맵 내부에 있는 모든 영수증을 출력해 주는 함수
void seller::show_all_receipt()
{
    for (auto& rct : receipt)
    {
        int tot = 0;
        cout << "------------------------------------------" << endl;
        cout << "영수증 일련번호 : " << rct.first << endl;
        for (int i = 0; i < 5; i++)
        {
            if (rct.second[i].get_stock() != 0)
            {
                cout << rct.second[i].get_name() << " : " << rct.second[i].get_stock() << "개" << endl;
                tot += (rct.second[i].get_stock() * get_price(rct.second[i].get_name()));
            }
        }
        cout << "총 계 : " << tot << "원" << endl;
        cout << "------------------------------------------" << endl;
    }
}


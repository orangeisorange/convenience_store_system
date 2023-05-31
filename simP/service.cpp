#include "service.h"
#include <fstream>
using namespace std;

extern product receipt_product[5];					// product : show info what are you actually bought.
extern map<int, product*> receipt;				// int type(Ex. 영수증 번호 230529001: 23.05.29 첫번째 고객의 영수증.) 
extern int cur_day_receipt;


void Service::delName(std::string name) { //포인트 이용 고객 정보 삭제 함수
    int idx = this->check_Name(name); //이름 유무 확인
    if (idx != -1) {
        this->customerList.erase(customerList.begin() + idx);
        cout << "삭제가 완료되었습니다.";
    }
    else
        cout << "해당하는 이름의 고객이 존재하지 않습니다.";
}

int Service::check_Name(string name) //포인트 이용 또는 적립 시, 입력받은 이름이 등록되어 있는지 확인하는 함수
{
    int size = this->customerList.size(); //등록 고객 명수 확인
    for (int i = 0; i < size; i++) //customerList에 해당 이름이 있는지 확인하기 윈한 for문
    {
        if (this->customerList.at(i).names == name)
            return i;
    }
    return -1;
}

void Service::getPoint(std::string name, int amount) //포인트 적립 함수
{
    int idx = this->check_Name(name);
    if (idx != -1) {
        this->customerList.at(idx).points += amount; //해당 고객 포인트 증가
        cout << "적립이 완료되었습니다.";
    }
    else {
        cout << "해당하는 이름의 고객이 존재하지 않습니다." << endl;
        cout << "서비스를 이용하시려면 메인화면에서 고객 등록을 완료해주시기 바랍니다.";
    }

}


void Service::usePoint(std::string name) { //상품 결제 중, 포인트 결제 함수
    int size = this->customerList.size();
    int point;
    int idx = this->check_Name(name);
    point = customerList.at(idx).points;
    if (idx == -1) {
        cout << "해당하는 이름의 고객이 존재하지 않습니다." << endl;
        return;
    }
    cout << "잔여 포인트" << point << endl;

    if (point > 0) {
        // 포인트 사용 시 포인트 차감
        int paymentAmount;
        cout << "사용할 포인트를 입력해주세요: ";
        cin >> paymentAmount;

        if (paymentAmount <= point) {
            this->subPoint(paymentAmount, idx);
            cout << "결제가 완료되었습니다." << endl;
        }
        else {
            cout << "포인트가 부족합니다. 카드로 결제하시기 바랍니다" << endl;
            useCard();
        }
    }
    else {
        cout << "남은 포인트가 없습니다. 카드로 결제하시기 바랍니다" << endl;
        useCard();
    }

}

void Service::subPoint(int amount, int idx_at) //포인트 결제 시, 포인트 차감 함수
{
    this->customerList.at(idx_at).points += amount;
}


void Service::useCard() { //카드 결제 함수
    cout << "결제가 완료되었습니다." << endl;
}

void Service::order(seller admin) {
    cout << "상품을 선택해주세요" << endl;
    admin.show_product(); //상품 현황 출력
    string pointcustomer; //고객 이름 입력받기 위한 변수
    int num = 0;
    string buyproduct[100];
    int buystock[100] = { 0 };
    char choice;
    int sum = 0; //총 결제 금액 변수
    while (true) {
        cout << "상품명: ";
        cin >> buyproduct[num];
        cout << "수량: ";
        cin >> buystock[num];
        for (int i = 0; i < 5; i++)
            if (receipt_product[i].get_name() == buyproduct[num]) //상품명 확인용
                receipt_product[i].stock_plus(buystock[num]); //상품 수량 확인용
        cout << "더 주문하시겠습니까? (y/n)";
        cin >> choice;
        if (choice == 'y') {
            sum += admin.get_price(buyproduct[num]) * buystock[num]; //수익 계산
            num++; //index 증가
            continue;
        }
        else {
            sum += admin.get_price(buyproduct[num]) * buystock[num];
            break;
        }
    }
    cout << "포인트로 결제하시겠습니까?(y/n): ";
    cin >> choice;
    if (choice == 'y') {
        cout << "고객 이름을 입력해주세요: ";
        cin >> pointcustomer;
        usePoint(pointcustomer); //포인트 사용 함수 호출
    }
    else
        useCard();
    for (int i = 0; i <= num; i++) {
        cout << buyproduct[i] << endl;
        admin.payment_complete(buyproduct[i], buystock[i], admin.get_product(), product_income_pair); //구매 완료시 각종 정보들 저장하는 함수 호출
    }
    cout << "포인트를 적립하시겠습니까?(y/n): ";
    cin >> choice;
    if (choice == 'y') {
        cout << "고객 이름을 입력해주세요: ";
        cin >> pointcustomer;
        getPoint(pointcustomer, sum * 0.1); //결제 금액의 10% 적립
    }
    else
        cout << "감사합니다";

    // 장바구니에 담긴 것을 따로 깊은 복사를 하고, receipt map에 저장
    product* deep_copy_receipt_product = new product[5];
    for (int i = 0; i < 5; i++)
    {
        deep_copy_receipt_product[i].change_name(receipt_product[i].get_name());
        deep_copy_receipt_product[i].set_stock_zero();
        deep_copy_receipt_product[i].stock_plus(receipt_product[i].get_stock());
    }
    receipt.insert(make_pair(cur_day_receipt, deep_copy_receipt_product));

    // 구매 완료 후, 사용자에게 보여주는 영수증
    cout << "\n영수증" << endl;
    int tot = 0;
    cout << "------------------------------------------" << endl;
    cout << "영수증 일련번호 : " << cur_day_receipt << endl;
    for (int i = 0; i < 5; i++)
    {
        if (receipt[cur_day_receipt][i].get_stock() != 0)
        {
            cout << receipt[cur_day_receipt][i].get_name() << " : " << receipt[cur_day_receipt][i].get_stock() << "개" << endl;
            tot += (receipt[cur_day_receipt][i].get_stock() * admin.get_price(receipt[cur_day_receipt][i].get_name()));
        }
    }
    cout << "총 계 : " << tot << "원" << endl;
    day_income_pair[admin.get_cur_date()] += admin.get_income();
    cout << "------------------------------------------" << endl << endl;
    // 다음 영수증번호는 원래 영수증 번호 + 1 하여 겹치지 않도록 함
    cur_day_receipt += 1;

}

// 저장 형식 : 이름,포인트
void Service::save_customerList()
{
    ofstream fs("customerList.txt", ios::out);
    int size = customerList.size();
    for (int i = 0; i < size; i++)
    {
        fs << customerList.at(i).names << ',' << customerList.at(i).points << '\n';
    }
}

void Service::load_customerList()
{
    string tmp;
    string tmp_income;
    Customer c1;
    int tmp_inc;
    int tmp_cus;
    fstream fs("customerList.txt", ios::in);
    if (!fs) {
        cout << "" << "열기 오류" << endl;
    }
    customerList.clear();
    while (getline(fs, tmp, ',')) {
        tmp_cus = stoi(tmp);
        getline(fs, tmp_income);
        tmp_inc = stoi(tmp_income);
        c1.changeName(tmp);
        c1.setPoint(tmp_inc);
        customerList.push_back(c1);
    }
}

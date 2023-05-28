#include "service.h"
#include <fstream>
using namespace std;

void Service::delName(std::string name) { //포인트를 다 썼을 경우 고객이름 삭제 --> 아직 안넣음
    int idx = this->check_Name(name);
    if(idx!= -1)
        this->customerList.erase(customerList.begin() + idx);
}

int Service::check_Name(string name)
{
    int size = this->customerList.size();
    for (int i = 0; i < size; i++)
    {
        if (this->customerList.at(i).names == name)
            return i;
    }
    return -1;
}

void Service::getPoint(std::string name, int amount) //포인트 적립 (amount 안정함)
{
    int idx = this->check_Name(name);
    this->customerList.at(idx).points += amount;

}


void Service::usePoint(std::string name) { //결제
    int size = this->customerList.size();
    int point;
    int idx = this->check_Name(name);
    point = customerList.at(idx).points;
    if (idx == -1) {
        cout << "잘못된 사용자명 입력입니다. " << endl;
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

void Service::addPoint(int amount, int idx_at)
{
    this->customerList.at(idx_at).points += amount;
}

void Service::subPoint(int amount, int idx_at)
{
    this->customerList.at(idx_at).points += amount;
}


void Service::useCard() {
    cout << "결제가 완료되었습니다." << endl;
}

void Service::order(seller admin) {
    cout << "상품을 선택해주세요" << endl;
    admin.show_product();
    string pointcustomer;
    int num = 0;
    string buyproduct[5];
    int buystock[5] = { 0 };
    char choice;
    int sum = 0;
    while (true) {
        cout << "상품명: ";
        cin >> buyproduct[num];
        cout << "수량: ";
        cin >> buystock[num];
        cout << "더 주문하시겠습니까? (y/n)";
        cin >> choice;
        if (choice == 'y') {
            sum += admin.get_price(buyproduct[num]) * buystock[num];
            num++;
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
        usePoint(pointcustomer);
    }
    else
        useCard();
    for (int i = 0; i <= num; i++) {
        cout << buyproduct[i] << endl;
        admin.payment_complete(buyproduct[i], buystock[i],admin.get_product(),product_income_pair, day_income_pair);
    }
    cout << "포인트를 적립하시겠습니까?(y/n): ";
    cin >> choice;
    if (choice == 'y') {
        cout << "고객 이름을 입력해주세요: ";
        cin >> pointcustomer;
        getPoint(pointcustomer, sum * 0.1);

    }
    else
        cout << "감사합니다";

}

void Service::save_customerList()
{
    ofstream fs("customerList.txt", ios::app);
    int size = customerList.size();
    for (int i = 0; i < size; i++)
    {
        fs << customerList.at(i).names << ',' << customerList.at(i).points << '\n';
    }
}

void Service::load_customerList()
{
    
}






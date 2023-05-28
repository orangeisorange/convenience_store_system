#include "service.h"
using namespace std;

void Service::delName(std::string name) { //포인트를 다 썼을 경우 고객이름 삭제 --> 아직 안넣음
    for (auto it = customerList.begin(); it != customerList.end(); ++it) {
        for (int i = 0; i < it->names.size(); i++) {
            if (it->names[i] == name) {
                it->names.erase(it->names.begin() + i);
                it->points.erase(it->points.begin() + i);
                return;
            }
        }
    }
}

void Service::getPoint(std::string name, int amount) //포인트 적립 (amount 안정함)
{
    for (auto& customer : customerList) {
        for (int i = 0; i < customer.names.size(); i++) {
            if (customer.names[i] == name) {
                customer.points[i].addPoint(amount); //amount만 정하면 됨
                return;
            }
        }
    }
}


void Service::usePoint(std::string name) { //결제

    int point = showPoint(name);
    cout << "잔여 포인트" << point << endl;

    if (point > 0) {
        // 포인트 사용 시 포인트 차감
        int paymentAmount;
        cout << "사용할 포인트를 입력해주세요: ";
        cin >> paymentAmount;

        if (paymentAmount <= point) {
            for (auto& customer : customerList) {
                for (size_t i = 0; i < customer.names.size(); ++i) {
                    if (customer.names[i] == name) {
                        customer.points[i].subPoint(paymentAmount);
                        return;
                    }
                }
            }
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


void Service::useCard() {
    cout << "결제가 완료되었습니다." << endl;
}

void Service::order(std::string name, seller admin) {
    cout << "상품을 선택해주세요" << endl;
    admin.show_product();
    string pointcustomer;
    int num = 0;
    string buyproduct[5];
    int buystock[5];
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
        admin.payment_complete(buyproduct[i], buystock[i],admin.get_product());
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






#include "customer.h"
using namespace std;

void Customer::setName(std::string newName) { //고객 이름 입력
    this->names = newName;
}

void Customer::registerUser(Customer& customer) {
    std::string userName;
    cout << "고객 이름을 입력하세요: ";
    cin >> userName;
    customer.addName(userName);
}


void Customer::changeName(std::string newName) { //고객 이름 변경
    this->names = newName;
}

void Customer::setPoint(std::string name, int value) { //사용자 이름별 포인트 적립
    this->points += value;
}

int Customer::showPoint() { //포인트 현황 리턴
    return this->points;
}
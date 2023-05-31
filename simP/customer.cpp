#include "customer.h"
using namespace std;

void Customer::setName(std::string newName) { //고객 이름 받는 함수
    this->names = newName;
}

void Customer::changeName(std::string newName) { //고객 이름 변경 함수
    this->names = newName;
}

void Customer::setPoint(int value) { //customerlist를 로드할 때 사용자별 포인트를 나타내기 위한 함수
    this->points += value;
}

int Customer::showPoint() { //포인트 현황 리턴
    return this->points;
}
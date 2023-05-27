#include "customer.h"
#include <string>
void Point::addPoint(int amount) { //포인트를 얼만큼 적립하거나 사용할지 변수를 안정해서 amount로 함
    value += amount;
}

void Point::subPoint(int amount) {
    value -= amount;
}

void Customer::addName(std::string newName) { //고객 이름 입력
    names.push_back(newName);
    points.push_back(Point());
}

void Customer::changeName(std::string oldName, std::string newName) { //고객 이름 변경
    for (size_t i = 0; i < names.size(); ++i) {
        if (names[i] == oldName) {
            names[i] = newName;
            return;
        }
    }
}

void Customer::setPoint(std::string name, int value) { //사용자 이름별 포인트 적립
    for (size_t i = 0; i < names.size(); ++i) {
        if (names[i] == name) {
            points[i].value = value;
            return;
        }
    }
}

int Customer::showPoint(std::string name) { //포인트 현황 리턴
    for (size_t i = 0; i < names.size(); ++i) {
        if (names[i] == name) {
            return points[i].value;
        }
    }
    return 0;  // 해당 이름을 찾지 못한 경우 기본값인 0 반환
}
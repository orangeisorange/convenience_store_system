#include "customer.h"
using namespace std;

void Customer::setName(std::string newName) { //�� �̸� �޴� �Լ�
    this->names = newName;
}

void Customer::changeName(std::string newName) { //�� �̸� ���� �Լ�
    this->names = newName;
}

void Customer::setPoint(int value) { //customerlist�� �ε��� �� ����ں� ����Ʈ�� ��Ÿ���� ���� �Լ�
    this->points += value;
}

int Customer::showPoint() { //����Ʈ ��Ȳ ����
    return this->points;
}
#include "customer.h"
using namespace std;

void Customer::setName(std::string newName) { //�� �̸� �Է�
    this->names = newName;
}

void Customer::registerUser(Customer& customer) {
    std::string userName;
    cout << "�� �̸��� �Է��ϼ���: ";
    cin >> userName;
    customer.addName(userName);
}


void Customer::changeName(std::string newName) { //�� �̸� ����
    this->names = newName;
}

void Customer::setPoint(std::string name, int value) { //����� �̸��� ����Ʈ ����
    this->points += value;
}

int Customer::showPoint() { //����Ʈ ��Ȳ ����
    return this->points;
}
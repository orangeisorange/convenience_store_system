#include "customer.h"
#include <string>
void Point::addPoint(int amount) { //����Ʈ�� ��ŭ �����ϰų� ������� ������ �����ؼ� amount�� ��
    value += amount;
}

void Point::subPoint(int amount) {
    value -= amount;
}

void Customer::addName(std::string newName) { //�� �̸� �Է�
    names.push_back(newName);
    points.push_back(Point());
}

void Customer::changeName(std::string oldName, std::string newName) { //�� �̸� ����
    for (size_t i = 0; i < names.size(); ++i) {
        if (names[i] == oldName) {
            names[i] = newName;
            return;
        }
    }
}

void Customer::setPoint(std::string name, int value) { //����� �̸��� ����Ʈ ����
    for (size_t i = 0; i < names.size(); ++i) {
        if (names[i] == name) {
            points[i].value = value;
            return;
        }
    }
}

int Customer::showPoint(std::string name) { //����Ʈ ��Ȳ ����
    for (size_t i = 0; i < names.size(); ++i) {
        if (names[i] == name) {
            return points[i].value;
        }
    }
    return 0;  // �ش� �̸��� ã�� ���� ��� �⺻���� 0 ��ȯ
}
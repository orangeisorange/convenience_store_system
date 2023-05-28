#include "service.h"
using namespace std;

void Service::delName(std::string name) { //����Ʈ�� �� ���� ��� ���̸� ���� --> ���� �ȳ���
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

void Service::getPoint(std::string name, int amount) //����Ʈ ���� (amount ������)
{
    for (auto& customer : customerList) {
        for (int i = 0; i < customer.names.size(); i++) {
            if (customer.names[i] == name) {
                customer.points[i].addPoint(amount); //amount�� ���ϸ� ��
                return;
            }
        }
    }
}


void Service::usePoint(std::string name) { //����

    int point = showPoint(name);
    cout << "�ܿ� ����Ʈ" << point << endl;

    if (point > 0) {
        // ����Ʈ ��� �� ����Ʈ ����
        int paymentAmount;
        cout << "����� ����Ʈ�� �Է����ּ���: ";
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
            cout << "������ �Ϸ�Ǿ����ϴ�." << endl;
        }
        else {
            cout << "����Ʈ�� �����մϴ�. ī��� �����Ͻñ� �ٶ��ϴ�" << endl;
            useCard();
        }
    }
    else {
        cout << "���� ����Ʈ�� �����ϴ�. ī��� �����Ͻñ� �ٶ��ϴ�" << endl;
        useCard();
    }

}


void Service::useCard() {
    cout << "������ �Ϸ�Ǿ����ϴ�." << endl;
}

void Service::order(std::string name, seller admin) {
    cout << "��ǰ�� �������ּ���" << endl;
    admin.show_product();
    string pointcustomer;
    int num = 0;
    string buyproduct[5];
    int buystock[5];
    char choice;
    int sum = 0;
    while (true) {
        cout << "��ǰ��: ";
        cin >> buyproduct[num];
        cout << "����: ";
        cin >> buystock[num];
        cout << "�� �ֹ��Ͻðڽ��ϱ�? (y/n)";
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
    cout << "����Ʈ�� �����Ͻðڽ��ϱ�?(y/n): ";
    cin >> choice;
    if (choice == 'y') {
        cout << "�� �̸��� �Է����ּ���: ";
        cin >> pointcustomer;
        usePoint(pointcustomer);
    }
    else
        useCard();
    for (int i = 0; i <= num; i++) {
        admin.payment_complete(buyproduct[i], buystock[i],admin.get_product());
    }
    cout << "����Ʈ�� �����Ͻðڽ��ϱ�?(y/n): ";
    cin >> choice;
    if (choice == 'y') {
        cout << "�� �̸��� �Է����ּ���: ";
        cin >> pointcustomer;
        getPoint(pointcustomer, sum * 0.1);

    }
    else
        cout << "�����մϴ�";

}






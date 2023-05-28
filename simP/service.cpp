#include "service.h"
#include <fstream>
using namespace std;

void Service::delName(std::string name) { //����Ʈ�� �� ���� ��� ���̸� ���� --> ���� �ȳ���
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

void Service::getPoint(std::string name, int amount) //����Ʈ ���� (amount ������)
{
    int idx = this->check_Name(name);
    this->customerList.at(idx).points += amount;

}


void Service::usePoint(std::string name) { //����
    int size = this->customerList.size();
    int point;
    int idx = this->check_Name(name);
    point = customerList.at(idx).points;
    if (idx == -1) {
        cout << "�߸��� ����ڸ� �Է��Դϴ�. " << endl;
        return;
    }
    cout << "�ܿ� ����Ʈ" << point << endl;

    if (point > 0) {
        // ����Ʈ ��� �� ����Ʈ ����
        int paymentAmount;
        cout << "����� ����Ʈ�� �Է����ּ���: ";
        cin >> paymentAmount;

        if (paymentAmount <= point) {
            this->subPoint(paymentAmount, idx);
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

void Service::addPoint(int amount, int idx_at)
{
    this->customerList.at(idx_at).points += amount;
}

void Service::subPoint(int amount, int idx_at)
{
    this->customerList.at(idx_at).points += amount;
}


void Service::useCard() {
    cout << "������ �Ϸ�Ǿ����ϴ�." << endl;
}

void Service::order(seller admin) {
    cout << "��ǰ�� �������ּ���" << endl;
    admin.show_product();
    string pointcustomer;
    int num = 0;
    string buyproduct[5];
    int buystock[5] = { 0 };
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
        cout << buyproduct[i] << endl;
        admin.payment_complete(buyproduct[i], buystock[i],admin.get_product(),product_income_pair, day_income_pair);
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






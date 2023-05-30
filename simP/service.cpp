#include "service.h"
#include <fstream>
using namespace std;

extern product receipt_product[5];					// product : show info what are you actually bought.
extern map<int, product*> receipt;				// int type(Ex.230529001 23.05.29 1th customer's receipt.) 
extern product receipt_product[5];
extern int cur_day_receipt;


void Service::delName(std::string name) { //����Ʈ�� �� ���� ��� ���̸� ���� --> ���� �ȳ���
    int idx = this->check_Name(name);
    if (idx != -1) {
        this->customerList.erase(customerList.begin() + idx);
        cout << "������ �Ϸ�Ǿ����ϴ�.";
    }
    else
        cout << "�ش��ϴ� �̸��� ���� �������� �ʽ��ϴ�.";
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
    if (idx != -1) {
        this->customerList.at(idx).points += amount;
        cout << "������ �Ϸ�Ǿ����ϴ�.";
    }
    else {
        cout << "�ش��ϴ� �̸��� ���� �������� �ʽ��ϴ�." << endl;
        cout << "���񽺸� �̿��Ͻ÷��� ����ȭ�鿡�� �� ����� �Ϸ����ֽñ� �ٶ��ϴ�.";
    }

}


void Service::usePoint(std::string name) { //����
    int size = this->customerList.size();
    int point;
    int idx = this->check_Name(name);
    point = customerList.at(idx).points;
    if (idx == -1) {
        cout << "�ش��ϴ� �̸��� ���� �������� �ʽ��ϴ�." << endl;
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
    string buyproduct[100];
    int buystock[100] = { 0 };
    char choice;
    int sum = 0;
    while (true) {
        cout << "��ǰ��: ";
        cin >> buyproduct[num];
        cout << "����: ";
        cin >> buystock[num];
        for (int i = 0; i < 5; i++)
            if (receipt_product[i].get_name() == buyproduct[num])
                receipt_product[i].stock_plus(buystock[num]);
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
        admin.payment_complete(buyproduct[i], buystock[i], admin.get_product(), product_income_pair, day_income_pair,receipt );
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
    ofstream fs("customerList.txt", ios::out);
    int size = customerList.size();
    for (int i = 0; i < size; i++)
    {
        fs << customerList.at(i).names << ',' << customerList.at(i).points << '\n';
    }
}

void Service::load_customerList()
{
    string tmp;
    string tmp_income;
    Customer c1;
    int tmp_inc;
    int tmp_cus;
    fstream fs("customerList.txt", ios::in);
    if (!fs) {
        cout << "" << "���� ����" << endl;
    }
    customerList.clear();
    while (getline(fs, tmp, ',')) {
        tmp_cus = stoi(tmp);
        getline(fs, tmp_income);
        tmp_inc = stoi(tmp_income);
        c1.changeName(tmp);
        c1.setPoint(tmp_inc);
        customerList.push_back(c1);
    }

}





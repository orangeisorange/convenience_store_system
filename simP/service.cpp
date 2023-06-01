#include "service.h"
#include <fstream>
using namespace std;

extern product receipt_product[5];					// product : show info what are you actually bought.
extern map<int, product*> receipt;				// int type(Ex. ������ ��ȣ 230529001: 23.05.29 ù��° ���� ������.) 
extern int cur_day_receipt;
extern map<string, int> product_income_pair;

void Service::delName(std::string name) { //����Ʈ �̿� �� ���� ���� �Լ�
    int idx = this->check_Name(name); //�̸� ���� Ȯ��
    if (idx != -1) {
        this->customerList.erase(customerList.begin() + idx);
        cout << "������ �Ϸ�Ǿ����ϴ�.";
    }
    else
        cout << "�ش��ϴ� �̸��� ���� �������� �ʽ��ϴ�.";
}

int Service::check_Name(string name) //����Ʈ �̿� �Ǵ� ���� ��, �Է¹��� �̸��� ��ϵǾ� �ִ��� Ȯ���ϴ� �Լ�
{
    int size = this->customerList.size(); //��� �� ��� Ȯ��
    for (int i = 0; i < size; i++) //customerList�� �ش� �̸��� �ִ��� Ȯ���ϱ� ���� for��
    {
        if (this->customerList.at(i).names == name)
            return i;
    }
    return -1;
}

void Service::getPoint(std::string name, int amount) //����Ʈ ���� �Լ�
{
    int idx = this->check_Name(name);
    if (idx != -1) {
        this->customerList.at(idx).points += amount; //�ش� �� ����Ʈ ����
        cout << "������ �Ϸ�Ǿ����ϴ�.";
    }
    else {
        cout << "�ش��ϴ� �̸��� ���� �������� �ʽ��ϴ�." << endl;
        cout << "���񽺸� �̿��Ͻ÷��� ����ȭ�鿡�� �� ����� �Ϸ����ֽñ� �ٶ��ϴ�.";
    }

}


void Service::usePoint(std::string name) { //��ǰ ���� ��, ����Ʈ ���� �Լ�
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

void Service::subPoint(int amount, int idx_at) //����Ʈ ���� ��, ����Ʈ ���� �Լ�
{
    this->customerList.at(idx_at).points += amount;
}


void Service::useCard() { //ī�� ���� �Լ�
    cout << "������ �Ϸ�Ǿ����ϴ�." << endl;
}

void Service::order(seller admin) {
    cout << "��ǰ�� �������ּ���" << endl;
    admin.show_product(); //��ǰ ��Ȳ ���
    string pointcustomer; //�� �̸� �Է¹ޱ� ���� ����
    int num = 0;
    string buyproduct[100];
    int buystock[100] = { 0 };
    char choice;
    int sum = 0; //�� ���� �ݾ� ����
    while (true) {
        cout << "��ǰ��: ";
        cin >> buyproduct[num];
        cout << "����: ";
        cin >> buystock[num];
        for (int i = 0; i < 5; i++)
            if (receipt_product[i].get_name() == buyproduct[num]) //��ǰ�� Ȯ�ο�
                receipt_product[i].stock_plus(buystock[num]); //��ǰ ���� Ȯ�ο�
        cout << "�� �ֹ��Ͻðڽ��ϱ�? (y/n)";
        cin >> choice;
        if (choice == 'y') {
            sum += admin.get_price(buyproduct[num]) * buystock[num]; //���� ���
            num++; //index ����
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
        usePoint(pointcustomer); //����Ʈ ��� �Լ� ȣ��
    }
    else
        useCard();
    for (int i = 0; i <= num; i++) {
        cout << buyproduct[i] << endl;
        admin.payment_complete(buyproduct[i], buystock[i], admin.get_product(), product_income_pair); //���� �Ϸ�� ���� ������ �����ϴ� �Լ� ȣ��
    }
    cout << "����Ʈ�� �����Ͻðڽ��ϱ�?(y/n): ";
    cin >> choice;
    if (choice == 'y') {
        cout << "�� �̸��� �Է����ּ���: ";
        cin >> pointcustomer;
        getPoint(pointcustomer, sum * 0.1); //���� �ݾ��� 10% ����
    }
    else
        cout << "�����մϴ�";

    // ��ٱ��Ͽ� ��� ���� ���� ���� ���縦 �ϰ�, receipt map�� ����
    product* deep_copy_receipt_product = new product[5];
    for (int i = 0; i < 5; i++)
    {
        deep_copy_receipt_product[i].change_name(receipt_product[i].get_name());
        deep_copy_receipt_product[i].set_stock_zero();
        deep_copy_receipt_product[i].stock_plus(receipt_product[i].get_stock());
    }
    receipt.insert(make_pair(cur_day_receipt, deep_copy_receipt_product));

    // ���� �Ϸ� ��, ����ڿ��� �����ִ� ������
    cout << "\n������" << endl;
    int tot = 0;
    cout << "------------------------------------------" << endl;
    cout << "������ �Ϸù�ȣ : " << cur_day_receipt << endl;
    for (int i = 0; i < 5; i++)
    {
        if (receipt[cur_day_receipt][i].get_stock() != 0)
        {
            cout << receipt[cur_day_receipt][i].get_name() << " : " << receipt[cur_day_receipt][i].get_stock() << "��" << endl;
            tot += (receipt[cur_day_receipt][i].get_stock() * admin.get_price(receipt[cur_day_receipt][i].get_name()));
        }
    }
    cout << "�� �� : " << tot << "��" << endl;
    day_income_pair[admin.get_cur_date()] += admin.get_income();
    cout << "------------------------------------------" << endl << endl;
    // ���� ��������ȣ�� ���� ������ ��ȣ + 1 �Ͽ� ��ġ�� �ʵ��� ��
    cur_day_receipt += 1;

}

// ���� ���� : �̸�,����Ʈ
void Service::save_customerList()
{
    ofstream fs("customerList.txt", ios::out);
    int size = customerList.size();
    for (int i = 0; i < size; i++)
    {
        fs << customerList.at(i).names << ',' << customerList.at(i).points << '\n';
    }
}

// customerlist �� �ҷ����� �Լ�. ���α׷��� ���� �� ��, ����Ǿ�� ��.
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
        c1.setName(tmp);
        c1.setPoint(tmp_inc);
        customerList.push_back(c1);
    }
}


int Service::show_main_screen() {
    while (1)
    {
        int main_menu;
        cout << "\n������ ���񽺿� ���� ���� ȯ���մϴ�." << endl;
        cout << "1. �ֹ� ���(��������)" << endl;
        cout << "2. ������ ���(���ִ�����)" << endl;
        cout << "3. ������ ������ ���� ����" << endl;
        cout << "4. ������ ������ ���� ����" << endl;
        cout << "5. ���� " << endl;
        cout << "-->";
        cin >> main_menu;
        cin.ignore();
        if (main_menu >= 1 && main_menu <= 5) return main_menu;
        else cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��� �ּ��� " << endl << endl;
    }
}

void Service::init_product_income_map()
{
    product_income_pair.insert(make_pair("����", 0));
    product_income_pair.insert(make_pair("�ﰢ���", 0));
    product_income_pair.insert(make_pair("Ŀ��", 0));
    product_income_pair.insert(make_pair("���", 0));
    product_income_pair.insert(make_pair("��", 0));
}
int Service::show_seller_screen() {
    while (1)
    {
        int  seller_menu;
        cout << "\n1. ��� ä���" << endl;
        cout << "2. ��������� ���� ���" << endl;
        cout << "3. csv ���� �ҷ�����" << endl;
        cout << "4. csv ���Ͽ� �����ϱ�" << endl;
        cout << "5. ������ ���� �����ϱ�" << endl;
        cout << "6. ȯ��" << endl;
        cout << "7. ��ü ������ ���" << endl;
        cout << "8. ���� �޴���" << endl;
        cin >> seller_menu;
        if (seller_menu >= 1 && seller_menu <= 8) return seller_menu;
        else cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��� �ּ��� " << endl << endl;
    }
}


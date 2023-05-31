#include <iostream>
#include "customer.h"
#include "seller.h"

class Service : public Customer {
public:
    std::vector<Customer> customerList;
    void delName(std::string name); //����Ʈ �̿� �� ���� ���� �Լ�
    int check_Name(string name); //����Ʈ �̿� �Ǵ� ���� ��, �Է¹��� �̸��� ��ϵǾ� �ִ��� Ȯ���ϴ� �Լ�
    void getPoint(std::string name, int amount);//����Ʈ ���� �Լ�
    void usePoint(std::string name);  //��ǰ ���� ��, ����Ʈ ���� �Լ�
    void subPoint(int amount, int idx_at); //����Ʈ ���� ��, ����Ʈ ���� �Լ�
    void useCard();//ī�� ���� �Լ�
    void order(seller admin); //��ü���� �ֹ��ý��� ���� �Լ�
    void save_customerList(); //�� ����Ʈ ���� �Լ�
    void load_customerList(); //�� ����Ʈ �ε� �Լ�

    // �����Լ� ���� �Լ���
    int show_seller_screen();
    void init_product_income_map();
    int show_main_screen();
};
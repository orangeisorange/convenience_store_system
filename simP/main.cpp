#include "service.h"
#include <string>
using namespace std;

map<int, int> day_income_pair;          // Used when using csv file.  <day(ex.230528), that day's whole income>
map<string, int> product_income_pair;   // Used when using csv file.  <product_name, product's whole income>
map<int, product*> receipt;				// int type(Ex.230529001 23.05.29 1th customer's receipt.) 
product receipt_product[5];					// product : show info what are you actually bought.
int cur_day_receipt;

int show_main_screen() {
	while (1)
	{
		int main_menu;
		cout << "������ ���񽺿� ���� ���� ȯ���մϴ�." << endl;
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
void refresh_receipt_product(product* p)
{
	p[0].change_name("����");
	p[0].stock_minus(5);
	p[1].change_name("�ﰢ���");
	p[1].stock_minus(5);
	p[2].change_name("Ŀ��");
	p[2].stock_minus(5);
	p[3].change_name("���");
	p[3].stock_minus(5);
	p[4].change_name("��");
	p[4].stock_minus(5);
}
void insert_receipt()
{
	receipt.insert(make_pair(cur_day_receipt, receipt_product));
}
void init_product_income_map()
{
	product_income_pair.insert(make_pair("����", 0));
	product_income_pair.insert(make_pair("�ﰢ���", 0));
	product_income_pair.insert(make_pair("Ŀ��", 0));
	product_income_pair.insert(make_pair("���", 0));
	product_income_pair.insert(make_pair("��", 0));
}
int show_seller_screen() {
	while (1)
	{
		int  seller_menu;
		cout << "1. ��� ä���" << endl;
		cout << "2. ��������� ���� ���" << endl;
		cout << "3. csv ���� �ҷ�����" << endl;
		cout << "4. csv ���Ͽ� �����ϱ�" << endl;
		cout << "5. ������ ���� �����ϱ�" << endl;
		cout << "6. ȯ��" << endl;
		cout << "7. ���� �޴���" << endl;
		cin >> seller_menu;
		if (seller_menu >= 1 && seller_menu <= 7) return seller_menu;
		else cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��� �ּ��� " << endl << endl;
	}
}

int main()
{
	seller admin;
	Service s1;
	admin.init_csv();
	admin.load_receipt();
	init_product_income_map();
	s1.load_customerList();
	day_income_pair.insert(make_pair(admin.get_cur_date(), admin.get_income()));
	int turn_off_system = 1;
	while (turn_off_system)
	{
		int main_menu;
		main_menu = show_main_screen();
		switch (main_menu)
		{
		case 1:
		{
			refresh_receipt_product(receipt_product);
			s1.order(admin);
			break;
		}
		case 2:
		{
			cout << "��й�ȣ�� �Է��� �ּ��� " << endl;
			string input_pass;
			getline(cin, input_pass);
			if (!admin.check_Password(input_pass))
			{
				cout << "��й�ȣ �����Դϴ�." << endl;
				break;
			}
			cout << "������ ����Դϴ�." << endl;
			int seller_menu_breaker = 1;
			while (seller_menu_breaker) {
				int seller_menu;
				seller_menu = show_seller_screen();
				switch (seller_menu)
				{
				case 1:
					// ��� ä�ﶧ, �ϴ��� ��ü�� �� ä��
					admin.get_product()->stock_fill();
					break;
				case 2:
					admin.show_Data();
					break;
				case 3:
					admin.load_date_csv();
					admin.load_product_csv();
					break;
				case 4:
					admin.save_date_csv();
					admin.save_product_csv();
					break;
				case 5:
					admin.end_Day(admin.get_product());
					break;
				case 6:
				{
					admin.refund(admin.get_product());
					break;
				}
				case 7:
					seller_menu_breaker = 0;
					break;
				}
			}

			break;
		}
		case 3:
		{
			cout << "������ ������ �Է��� �ֽø� ������ ����� ���ϴ� !" << endl;
			cout << "������ ������  ������ �Է��� �ּ��� ! " << endl;
			string name_cus;
			cin >> name_cus;
			Customer tmp;
			tmp.setName(name_cus);
			s1.customerList.push_back(tmp);
			cout << "�� ����� �Ϸ�Ǿ����ϴ�.";
			break;
		}
		case 4:
		{
			cout << "������ ������ �Է��� �ֽø� ������ �����˴ϴ� !" << endl;
			string name_del;
			cin >> name_del;
			s1.delName(name_del);
			break;
		}
		case 5:
			turn_off_system = 0;
			break;
		}

	}
	// before close the program, save the customer's info and receipts.
	s1.save_customerList();
	admin.save_receipt();
}

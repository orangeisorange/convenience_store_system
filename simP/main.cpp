#include "service.h"
#include <string>
using namespace std;

std::map<int, int> day_income_pair;             // Used when using csv file.  <day(ex.230528), that day's whole income>
std::map<std::string, int> product_income_pair; // Used when using csv file.  <product_name, product's whole income>



int show_main_screen() {
	while (1)
	{
		int main_menu;
		cout << "������ ���񽺿� ���� ���� ȯ���մϴ�." << endl;
		cout << "1. �ֹ� ���(��������)" << endl;
		cout << "2. ������ ���(���ִ�����)" << endl;
		cout << "3. ���� " << endl;
		cin >> main_menu;
		cin.ignore();
		if (main_menu >= 1 && main_menu <= 3) return main_menu;
		else cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��� �ּ��� " << endl << endl;
	}
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
		cout << "6. ���� �޴���" << endl;
		cin >> seller_menu;
		if (seller_menu >= 1 && seller_menu <= 6) return seller_menu;
		else cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��� �ּ��� " << endl << endl;
	}
}

int main()
{
	seller admin;
	Service s1;
	init_product_income_map();
	int turn_off_system = 1;
	while (turn_off_system)
	{
		int main_menu;
		main_menu = show_main_screen();
		switch (main_menu)
		{
		case 1:
		{
			cout << "���� ������ ����Ʈ �ý��ۿ� ������ �Ǿ� �ֳ���? (Y / N)" << endl;
			char Y_N;
			string tmp_name;
			int idx = -1;
			cin >> Y_N;
			/* ���⼭ �� �̸� ��ϵ��ִ��� Ȯ���ؾ� ��. ������ ��Ź
			if (Y_N == 'y' || Y_N == 'Y')
			{
				cout << "��ϵ� �̸��� �Է��� �ּ���." << endl;
				cin >> tmp_name;
				idx = s1.check_Name(tmp_name);
				if (idx == -1) {
					cout << "��ϵ��� ���� ���Դϴ�." << endl;
				}
			}
			*/
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
			while(seller_menu_breaker){
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
					seller_menu_breaker = 0;
					break;
				}
			}

			break;
		}
		case 3:
			turn_off_system = 0;
			break;
		}

	}

}


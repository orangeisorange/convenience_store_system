#include "seller.h"
#include "service.h"
using namespace std;

int show_main_screen() {
	while (1)
	{
		int main_menu;
		cout << "������ ���񽺿� ���� ���� ȯ���մϴ�." << endl;
		cout << "1. ������ ���" << endl;
		cout << "2. �� ���" << endl;
		cout << "3. ���� " << endl;
		cin >> main_menu;
		if (main_menu >= 1 && main_menu <= 3) return main_menu;
		else cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��� �ּ��� " << endl << endl;
	}
}

int show_seller_screen() {
	while (1)
	{
		int  seller_menu;
		cout << "������ ����Դϴ�." << endl;
		cout << "1. ��� ä���" << endl;
		cout << "2. ��������� ���� ���" << endl;
		cout << "3. csv ���� �ҷ�����" << endl;
		cout << "4. csv ���Ͽ� �����ϱ�" << endl;
		cout << "5. ������ ���� �����ϱ�" << endl;
		cout << "6. ���� �޴���" << endl;
	}
}

int show_customer_screen(seller admin) {
	while (1)
	{
		int customer_menu;
		cout << "�ȳ��ϼ���. du������ �Դϴ�. " << endl;
		cout << "���� ������ �ִ� ��ǰ�� ������ �����ϴ�. " << endl;
		admin.show_product();
	}
}

int main()
{
	seller admin();
	int turn_off_system = 1;
	while (turn_off_system)
	{
		int main_menu;
		main_menu = show_main_screen();
		switch (main_menu)
		{
		case 1:
			break;
		case 2:
			break;
		case 3:
			turn_off_system = 0;
			break;
		}

	}

}


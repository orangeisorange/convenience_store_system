#include "seller.h"
#include "service.h"
using namespace std;

int show_main_screen() {
	while (1)
	{
		int main_menu;
		cout << "편의점 서비스에 오신 것을 환영합니다." << endl;
		cout << "1. 관리자 모드" << endl;
		cout << "2. 고객 모드" << endl;
		cout << "3. 종료 " << endl;
		cin >> main_menu;
		if (main_menu >= 1 && main_menu <= 3) return main_menu;
		else cout << "잘못된 입력입니다. 다시 입력해 주세요 " << endl << endl;
	}
}

int show_seller_screen() {
	while (1)
	{
		int  seller_menu;
		cout << "관리자 모드입니다." << endl;
		cout << "1. 재고 채우기" << endl;
		cout << "2. 현재까지의 매출 출력" << endl;
		cout << "3. csv 파일 불러오기" << endl;
		cout << "4. csv 파일에 저장하기" << endl;
		cout << "5. 오늘의 영업 종료하기" << endl;
		cout << "6. 상위 메뉴로" << endl;
	}
}

int show_customer_screen(seller admin) {
	while (1)
	{
		int customer_menu;
		cout << "안녕하세요. du편의점 입니다. " << endl;
		cout << "현재 진열되 있는 물품은 다음과 같습니다. " << endl;
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


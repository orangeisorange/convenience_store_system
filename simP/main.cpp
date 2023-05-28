#include "service.h"
#include <string>
using namespace std;

std::map<int, int> day_income_pair;             // Used when using csv file.  <day(ex.230528), that day's whole income>
std::map<std::string, int> product_income_pair; // Used when using csv file.  <product_name, product's whole income>



int show_main_screen() {
	while (1)
	{
		int main_menu;
		cout << "편의점 서비스에 오신 것을 환영합니다." << endl;
		cout << "1. 주문 모드(고객님전용)" << endl;
		cout << "2. 관리자 모드(점주님전용)" << endl;
		cout << "3. 종료 " << endl;
		cin >> main_menu;
		cin.ignore();
		if (main_menu >= 1 && main_menu <= 3) return main_menu;
		else cout << "잘못된 입력입니다. 다시 입력해 주세요 " << endl << endl;
	}
}
void init_product_income_map()
{
	product_income_pair.insert(make_pair("과자", 0));
	product_income_pair.insert(make_pair("삼각김밥", 0));
	product_income_pair.insert(make_pair("커피", 0));
	product_income_pair.insert(make_pair("담배", 0));
	product_income_pair.insert(make_pair("빵", 0));
}
int show_seller_screen() {
	while (1)
	{
		int  seller_menu;
		cout << "1. 재고 채우기" << endl;
		cout << "2. 현재까지의 매출 출력" << endl;
		cout << "3. csv 파일 불러오기" << endl;
		cout << "4. csv 파일에 저장하기" << endl;
		cout << "5. 오늘의 영업 종료하기" << endl;
		cout << "6. 상위 메뉴로" << endl;
		cin >> seller_menu;
		if (seller_menu >= 1 && seller_menu <= 6) return seller_menu;
		else cout << "잘못된 입력입니다. 다시 입력해 주세요 " << endl << endl;
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
			cout << "저희 편의점 포인트 시스템에 가입이 되어 있나요? (Y / N)" << endl;
			char Y_N;
			string tmp_name;
			int idx = -1;
			cin >> Y_N;
			/* 여기서 고객 이름 등록되있는지 확인해야 함. 구현좀 부탁
			if (Y_N == 'y' || Y_N == 'Y')
			{
				cout << "등록된 이름을 입력해 주세요." << endl;
				cin >> tmp_name;
				idx = s1.check_Name(tmp_name);
				if (idx == -1) {
					cout << "등록되지 않은 고객입니다." << endl;
				}
			}
			*/
			s1.order(admin);
			break;
		}
		case 2:
		{
			cout << "비밀번호를 입력해 주세요 " << endl;
			string input_pass;
			getline(cin, input_pass);
			if (!admin.check_Password(input_pass))
			{
				cout << "비밀번호 오류입니다." << endl;
				break;
			}
			cout << "관리자 모드입니다." << endl;
			int seller_menu_breaker = 1;
			while(seller_menu_breaker){
				int seller_menu;
				seller_menu = show_seller_screen();
				switch (seller_menu)
				{
				case 1:
					// 재고를 채울때, 일단은 전체를 다 채움
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


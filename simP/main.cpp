#include "service.h"
#include <string>
using namespace std;

map<int, int> day_income_pair;          // Used when using csv file.  <day(ex.230528), that day's whole income>
map<string, int> product_income_pair;   // Used when using csv file.  <product_name, product's whole income>
map<int, product*> receipt;				// int type(Ex.230529001 23.05.29 1th customer's receipt.) 
product receipt_product[5];					// product : show info what are you actually bought.
int cur_day_receipt;


int main()
{
	seller admin;
	Service s1;
	admin.init_csv();			// 프로그램에 필요한 파일 존재하는지 체크 및 없으면 생성
	admin.load_receipt();		// 영수증 파일 load
	s1.init_product_income_map();	// product_income_map초기화
	s1.load_customerList();		// 고객 리스트 load
	day_income_pair.insert(make_pair(admin.get_cur_date(), admin.get_income()));
	int turn_off_system = 1;	// turn_off_system이 0이면 프로그램종료
	while (turn_off_system)
	{
		int main_menu;
		main_menu = s1.show_main_screen();
		switch (main_menu)
		{
		case 1:		// 주문하기
		{
			admin.get_product()->refresh_receipt_product(receipt_product);
			s1.order(admin);
			break;
		}
		case 2:		// seller 모드 비밀번호는 1q2w3e4r!
		{
			cout << "비밀번호를 입력해 주세요 " << endl;
			string input_pass;
			getline(cin, input_pass);
			if (!admin.check_Password(input_pass))
			{
				cout << "비밀번호 오류입니다." << endl;
				break;
			}
			// 비밀번호를 통과한 경우
			cout << "관리자 모드입니다." << endl;
			int seller_menu_breaker = 1;
			while (seller_menu_breaker) {
				int seller_menu;
				seller_menu = s1.show_seller_screen();
				switch (seller_menu)
				{
				case 1:
					// 재고를 채울때, 전체를 다 채움(총량 5개)
					for (int i = 0; i < 5; i++)
						admin.get_product()[i].stock_fill();
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
					admin.show_all_receipt();
					break;
				case 8:
					seller_menu_breaker = 0;
					break;
				}
			}

			break;
		}
		case 3:
		{
			cout << "고객님의 성함을 입력해 주시면 계정이 만들어 집니다 !" << endl;
			cout << "공백을 제외한  성함을 입력해 주세요 ! " << endl;
			string name_cus;
			cin >> name_cus;
			Customer tmp;
			tmp.setName(name_cus);
			s1.customerList.push_back(tmp);
			cout << "고객 등록이 완료되었습니다.";
			break;
		}
		case 4:
		{
			cout << "고객님의 성함을 입력해 주시면 계정이 삭제됩니다 !" << endl;
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
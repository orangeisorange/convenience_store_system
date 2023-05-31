#include <iostream>
#include "customer.h"
#include "seller.h"

class Service : public Customer {
public:
    std::vector<Customer> customerList;
    void delName(std::string name); //포인트 이용 고객 정보 삭제 함수
    int check_Name(string name); //포인트 이용 또는 적립 시, 입력받은 이름이 등록되어 있는지 확인하는 함수
    void getPoint(std::string name, int amount);//포인트 적립 함수
    void usePoint(std::string name);  //상품 결제 중, 포인트 결제 함수
    void subPoint(int amount, int idx_at); //포인트 결제 시, 포인트 차감 함수
    void useCard();//카드 결제 함수
    void order(seller admin); //전체적인 주문시스템 구현 함수
    void save_customerList(); //고객 리스트 저장 함수
    void load_customerList(); //고객 리스트 로드 함수

    // 메인함수 관련 함수들
    int show_seller_screen();
    void init_product_income_map();
    int show_main_screen();
};
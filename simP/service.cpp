#include "service.h"

void Service::delName(std::string name) { //포인트를 다 썼을 경우 고객이름 삭제 --> 아직 안넣음
    for (auto it = customerList.begin(); it != customerList.end(); ++it) {
        for (size_t i = 0; i < it->names.size(); ++i) {
            if (it->names[i] == name) {
                it->names.erase(it->names.begin() + i);
                it->points.erase(it->points.begin() + i);
                return;
            }
        }
    }
}

void Service::getPoint(std::string name, int amount) { //포인트 적립 (amount 안정함)
    for (auto& customer : customerList) {
        for (size_t i = 0; i < customer.names.size(); ++i) {
            if (customer.names[i] == name) {
                customer.points[i].addPoint(amount);
                return;
            }
        }
    }
}


void Service::usePoint(std::string name) { //결제
    std::cout << "Do you want to pay with points? (y/n): ";
    char choice;
    std::cin >> choice;

    if (choice == 'y') {
        int point = showPoint(name);
        std::cout << "Remaining balance: $" << point << std::endl;

        if (point > 0) {
            // 포인트 사용 시 포인트 차감
            int paymentAmount;
            std::cout << "Enter payment amount with points: $";
            std::cin >> paymentAmount;

            if (paymentAmount <= point) {
                for (auto& customer : customerList) {
                    for (size_t i = 0; i < customer.names.size(); ++i) {
                        if (customer.names[i] == name) {
                            customer.points[i].subPoint(paymentAmount);
                            return;
                        }
                    }
                }
                std::cout << "Payment made with points!" << std::endl;
            }
            else {
                std::cout << "Invalid payment amount. Payment made with a card!" << std::endl;
                useCard();
            }
        }
        else {
            std::cout << "No points available. Payment made with a card!" << std::endl;
            useCard();
        }
    }
    else {
        std::cout << "Payment made with a card!" << std::endl;
    }
}


void Service::useCard() {
    std::cout << "Payment made with a card!" << std::endl;
}

void Service::order(std::string name) {
    // order함수도 왜 잇는지 모르겟....
}






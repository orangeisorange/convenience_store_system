#include "service.h"

void Service::delName(std::string name) { //����Ʈ�� �� ���� ��� ���̸� ���� --> ���� �ȳ���
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

void Service::getPoint(std::string name, int amount) { //����Ʈ ���� (amount ������)
    for (auto& customer : customerList) {
        for (size_t i = 0; i < customer.names.size(); ++i) {
            if (customer.names[i] == name) {
                customer.points[i].addPoint(amount);
                return;
            }
        }
    }
}


void Service::usePoint(std::string name) { //����
    std::cout << "Do you want to pay with points? (y/n): ";
    char choice;
    std::cin >> choice;

    if (choice == 'y') {
        int point = showPoint(name);
        std::cout << "Remaining balance: $" << point << std::endl;

        if (point > 0) {
            // ����Ʈ ��� �� ����Ʈ ����
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
    // order�Լ��� �� �մ��� �𸣰�....
}






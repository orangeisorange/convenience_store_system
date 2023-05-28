#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Customer {
public:
    string names;
    int points;
    void addName(string newName);
    void changeName(string newName);
    void setPoint(string name, int value);
    int showPoint();
    void registerUser(Customer& customer);
};
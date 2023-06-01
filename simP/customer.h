#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Customer {
public:
    string names;
    int points = 0;
    void setName(string newName);
    void setPoint(int value);
    int showPoint();
};
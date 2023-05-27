#include <string>
#include <vector>
struct Point {
    int value;
    Point() : value(0) {}
    void addPoint(int amount);
    void subPoint(int amount);
};
class Customer {

public:
    std::vector<std::string> names;
    std::vector<Point> points;
    void addName(std::string newName);
    void changeName(std::string oldName, std::string newName);
    void setPoint(std::string name, int value);
    int showPoint(std::string name);
};
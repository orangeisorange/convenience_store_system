#include "product.h"

product::product(std::string name)
{
	this->p_name = name;
	stock_fill();
}

product::product()
{
	stock_fill();
}

void product::stock_fill()
{
	this->stock = 5;
}

bool product::stock_minus(int num)
{
	if (num > stock) return false;
	stock -= num;
	return true;
}

void product::stock_plus(int num)
{
	stock += num;
}

void product::change_name(std::string new_name)
{
	this->p_name = new_name;
}

std::string product::get_name()
{
	return this->p_name;
}
void test() {

}
int product::get_stock()
{
	return stock;
}

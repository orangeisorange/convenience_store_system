#include "product.h"

void product::stock_fill()
{
	this->stock = 5;
}

void product::stock_minus(int num)
{
	stock -= num;
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

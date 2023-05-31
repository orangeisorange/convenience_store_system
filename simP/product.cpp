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

void product::refresh_receipt_product(product* p)
{
	p[0].change_name("°úÀÚ");
	p[0].set_stock_zero();
	p[1].change_name("»ï°¢±è¹ä");
	p[1].set_stock_zero();
	p[2].change_name("Ä¿ÇÇ");
	p[2].set_stock_zero();
	p[3].change_name("´ã¹è");
	p[3].set_stock_zero();
	p[4].change_name("»§");
	p[4].set_stock_zero();
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

void product::set_stock_zero()
{
	this->stock = 0;
}

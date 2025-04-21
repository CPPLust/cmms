#include "WoMen.h"
#include <iostream>

WoMen::WoMen()
{
	std::cout << "执行了WoMen::WoMen()" << std::endl;
}

WoMen::~WoMen()
{
	std::cout << "执行了WoMen::~WoMen" << std::endl;
}

int WoMen::fun()
{
	std::cout << "执行了WoMen::fun()" << std::endl;
	return 0;
}

void WoMen::eat()
{
	std::cout << "女人喜欢吃零食" << std::endl;
}

void WoMen::eat2()
{
	std::cout << "WoMen::eat2()" << std::endl;
}

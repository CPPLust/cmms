#include "Men.h"
#include <iostream>

Men::Men()
{
	std::cout << "执行了Men::Men()" << std::endl;
}
Men::~Men()
{
	std::cout << "执行了Men::~Men" << std::endl;
}

int Men::fun()
{
	std::cout << "执行了Men::fun()" << std::endl;
	return 0;
}

void Men::eat()
{
	std::cout << "男人喜欢吃零食" << std::endl;
}

void Men::eat2()
{
	std::cout << "Men::eat2()" << std::endl;
}
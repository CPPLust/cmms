#include "Men.h"
#include <iostream>

Men::Men()
{
	std::cout << "ִ����Men::Men()" << std::endl;
}
Men::~Men()
{
	std::cout << "ִ����Men::~Men" << std::endl;
}

int Men::fun()
{
	std::cout << "ִ����Men::fun()" << std::endl;
	return 0;
}

void Men::eat()
{
	std::cout << "����ϲ������ʳ" << std::endl;
}

void Men::eat2()
{
	std::cout << "Men::eat2()" << std::endl;
}
#include "Human.h"
#include <iostream>

Human::Human()
{
	std::cout << "ִ����Human::Human()" << std::endl;
}
Human::~Human()
{
	std::cout << "ִ����Human::~Human)" << std::endl;
}

Human::Human(int)
{
	std::cout << "ִ����Human::Human(int)" << std::endl;
}

int Human::fun()
{
	std::cout << "ִ����Human::fun()" << std::endl;
	return 0;
}
int Human::fun(int a, int c)
{
	std::cout << "ִ����fun(int a, int c)" << std::endl;
	return 0;
}

void Human::eat()
{
	std::cout << "����Ը�����ʳ" << std::endl;
}

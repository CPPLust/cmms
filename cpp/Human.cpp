#include "Human.h"
#include <iostream>

Human::Human()
{
	std::cout << "执行了Human::Human()" << std::endl;
}
Human::~Human()
{
	std::cout << "执行了Human::~Human)" << std::endl;
}

Human::Human(int)
{
	std::cout << "执行了Human::Human(int)" << std::endl;
}

int Human::fun()
{
	std::cout << "执行了Human::fun()" << std::endl;
	return 0;
}
int Human::fun(int a, int c)
{
	std::cout << "执行了fun(int a, int c)" << std::endl;
	return 0;
}

void Human::eat()
{
	std::cout << "人类吃各种粮食" << std::endl;
}

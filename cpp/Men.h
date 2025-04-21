#pragma once
#include "Human.h"
//class Men:public Human
class Men :public Human
{
public:
	Men();
	~Men();
	void eat() override;
	void eat2() override;
public:
	int fun();
	using Human::fun;

};


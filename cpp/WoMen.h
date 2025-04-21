#pragma once
#include "Human.h"
class WoMen :public Human
//class WoMen :protected Human
{
public:
	WoMen();
	~WoMen();
	
	void eat()override;
	void eat2() override;
public:
	int fun();

};


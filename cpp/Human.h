#pragma once
class Human
{
public:
	Human();
		Human(int);
		~Human();

public:
	virtual void eat();
	virtual void eat2() = 0;
public:
	int fun();
	int fun(int a, int c);
public:
	int m_Age;
	char m_Name[100];


};


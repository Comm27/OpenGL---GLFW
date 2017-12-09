#pragma once
#include <list>
#include <iostream>

class Callback
{
private:
	std::list<float(*)(float, float)> m_list;

public:
	void operator+=(float(*)(float, float));
	void operator-=(float(*)(float, float));

	void Ispis();
};
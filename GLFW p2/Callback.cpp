#include "Callback.h"

void Callback::operator+=(float(*a)(float, float))
{
	m_list.push_back(a);
}

void Callback::operator-=(float(*a)(float, float))
{
	m_list.remove(a);
}

void Callback::Ispis()
{
	std::list<float(*)(float, float)>::iterator it = m_list.begin();

	while (it != m_list.end())
	{
		std::cout << (*it)(5, 43) << std::endl;
		++it;
	}
}

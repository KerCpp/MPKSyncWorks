#include "_slaves.h"

/*
Funkcja sprawdzaj¹ca czy element jest w zbiorze
*/
bool onlyOnceRuleCtrl(const int &id, const std::vector<int> &vect)
{
	for each (const int &i in vect)
	{
		if (i == id)
			return true;
	}
	return false;
}

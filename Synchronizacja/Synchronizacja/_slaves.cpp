#include "_slaves.h"
#include <cmath>

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

int modulo(int Arg, int mod)
{
	return (Arg < 0) ? mod + (Arg%mod) : Arg%mod;
}
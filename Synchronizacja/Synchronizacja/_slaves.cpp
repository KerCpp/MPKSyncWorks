#include "_slaves.h"
#include <cmath>
#include <sstream>

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
//odejmowanie niebezpieczne!
int Ctime::operator-(Ctime rhs)
{
	if (m_h - rhs.m_h == 0)
		return m_m - rhs.m_m;
	else
		return 60 - (rhs.m_m - m_m);
}
const std::istream& operator>>(std::istream& INPUT, Ctime & OmNomNom)
{
	std::stringstream ss,ss1,ss2;
	char tmp[10];
    INPUT.getline(tmp,3,':');//pitupitu
	ss1 << tmp;
	ss1 >> OmNomNom.m_h;
	INPUT.getline(tmp,3, ':');//pitupitu
	ss2 << tmp;
	ss2 >> OmNomNom.m_m;
	INPUT.getline(tmp,3, ':');//pitupitu
	ss << tmp;
	ss >> OmNomNom.m_s;
	return INPUT;
}
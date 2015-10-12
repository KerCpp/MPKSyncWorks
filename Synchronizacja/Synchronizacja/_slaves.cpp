#include "_slaves.h"
#include <cmath>
#include <sstream>
#include <algorithm>

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
//takie tam do sortowania comb i perm
void __presort(std::vector<int>& c, std::vector<int>& p)
{
	std::vector<ls> sorter;
	for (auto i = 0u; i < c.size(); i++)
		sorter.push_back(ls(p[i], c[i]));
	std::sort(sorter.begin(), sorter.end(), [](const ls &arg1, const ls &arg2)->bool{return arg1.m_startTime > arg2.m_startTime; });
	for (auto i = 0u; i < c.size(); i++)
	{
		c[i] = sorter[i][1];
		p[i] = sorter[i][0];
	}
}
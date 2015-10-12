#include "przystanek.h"
#include "kombinacje.h"
#include <cmath>
#include <numeric>

//czy jest petla
bool CStop::isItTerminus() const
{
	return m_terminus;
}
//czy jest wezlem
bool CStop::isItKnot() const
{
	return m_knot;
}
//ustaw wezel
void CStop::setKnot()
{
	m_knot = true;
}
//zlikwiduj wezel
void CStop::unsetKnot()
{
	m_knot = false;
}
//ustaw petle
void CStop::setTerminus()
{
	m_terminus = true;
}
//zniszcz petle 666 :D
void CStop::unsetTerminus()
{
	m_terminus = false;
}
//ilosc lini zatrzymujacyhc sie na przystanku
const int CStop::numOfLines() const
{
	return m_lines.size();
}
//id przystanku
const int CStop::id() const
{
	return m_id;
}
//ocenia wêze³
int CStop::rating() const
{
	if (m_tTable.size() == 1) return 0;
	int stopRate = INT_MIN;
	Ccombinations comb(numOfLines(), 15, 0);
	for(auto &c : comb.retComb())
	{
		auto cCopy(c);
		std::partial_sum(c.begin(), c.end(), cCopy.begin());
		int test = 0 - _cumPowSum(cCopy);
		//do genetycznego dopisac
		//dopuszczalne odstepy
		//warunek rozkladu linii
		if (test == 0)  return 0;
		if (stopRate < test)
			stopRate = test;
	}
	return stopRate;
}
//liczy sume kwadratow Odchylek
int CStop::_cumPowSum(const std::vector<int>& comb) const
{
	int sum = 0;
	auto tT = m_tTable.back().m_startTime;
	auto c = comb.back();
	int tTDelay = tT == c ? 0 : c - tT;
	for (size_t i = 0; i < m_tTable.size(); i++)
	{
		auto diff = abs(m_tTable[i].m_startTime - comb[i] + tTDelay);
		sum += diff*diff;
	}
	return sum;
}
//przestawia odjazdy niebezpieczna/ mozna zmienic dlugosc wektora przypadkiem
std::vector<ls>& CStop::setTTable()
{
	return m_tTable;
}
//przestawia odjazdy bezpieczna
const std::vector<ls>& CStop::setTTable() const
{
	return m_tTable;
}
//sprawdza czy prawidlowo wypelniony
bool CStop::isGood() const
{
	for (auto i = 0u; i < m_tTable.size() - 1; i++)
	{
		if (m_tTable[i].m_startTime == m_tTable[i+1].m_startTime)//jesli przyjazd w tym samym czasie
			return false;
	}
	return true;
	////////////////////warunki rozkladu , odstepu
}
//dodanie listy do wektora
void CStop::addLine(int id)
{
	m_lines.push_back(id);
}
//zrwaca wektor lini
const std::vector<int>& CStop::lineList() const
{
	return m_lines;
}
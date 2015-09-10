#include "przystanek.h"
#include "kombinacje.h"
#include <cmath>

//konstrukytor
CStop::CStop(){}
//destruktor
CStop::~CStop(){}
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
	int stopRate = INT_MIN;
	Ccombinations comb(numOfLines(), 12, 0);
	for each (const auto &c in comb.retComb())
	{
		int test = 0 - _cumPowSum(c);
		//do genetycznego dopisac
		//dopuszczalne odstepy
		//warunek rozkladu linii
		if (stopRate < test)
			stopRate = test;
	}
	return stopRate;
}
//liczy sume kwadratow Odchylek
int CStop::_cumPowSum(const std::vector<int>& comb) const
{
	int sum = 0;
	for (size_t i = 0; i < m_tTable.size(); i++)
	{
		auto diff = abs(m_tTable[i].m_startTime - comb[i]);
		sum += diff*diff;
	}
}
//przestawia odjazdy niebezpieczna/ mozna zmienic dlugosc wektora przypadkiem
const std::vector<ls>& CStop::setTTable()
{
	return m_tTable;
}
//przestawia odjazdy bezpieczna
const std::vector<ls>& CStop::setTTable() const
{
	return m_tTable;
}
bool CStop::isGood() const
{
	////////////////////
}
#include "mpolaczen.h"
#include <list>
/*
Konstruktor
fileName - nazwa pliku z danymi
*/
CconnectionMatrix::CconnectionMatrix(std::string fileName)
{
	CconnectionMatrix();
}
/*
Zwraca gdzie dana linia siê zatrzymuje
lineId -id lini
*/
std::vector<int> CconnectionMatrix::whereLineStops(const int &lineId) const
{
	std::vector<int> tmp;
	for (auto i = 0; i < m_numOfStops; i++)
	{
		if (m_table[lineId][i] == true)
			tmp.push_back(i);
	}
	return tmp;
}
/*
Zwraca jakie linie zatrzymuj¹ siê na wybranym przystanku
stopId-numer przystanku
*/
std::vector<int> CconnectionMatrix::whichLineStopsHere(const int &stopId) const
{
	std::vector<int> tmp;
	for (auto i = 0; i < m_numOfLines; i++)
	{
		if (m_table[i][stopId] == true)
			tmp.push_back(i);
	}
	return tmp;
}
/*
Czy linia zatrzymuje sie na przystanku
*/
bool CconnectionMatrix::ifLineStopsHere(const int &line, const int &stop) const
{
	return m_table[line][stop];
}
/*
Ogólna iloœæ lini
*/
int CconnectionMatrix::numOfLines() const
{
	return m_numOfLines;
}
/*
Ogólna iloœæ przystanków
*/
int CconnectionMatrix::numOfStops() const
{
	return m_numOfStops;
}
//Opisuje grafskierowany przystankow na macierzy
void CconnectionMatrix::_fillGraph()
{
	for (auto i = 0; i < m_numOfLines; i++)
	{
		auto &tmp = m_allLines[i].stopsList();
		auto iteratorOfStops = std::begin(tmp);
		while (iteratorOfStops != std::end(tmp))
		{
			iteratorOfStops++;
			auto it = iteratorOfStops;
			it--;
			m_graphRepresentingStopsConnections[*it][*iteratorOfStops].m_conj = true;
		}
	}
}
//Oznacza wêz³y
void CconnectionMatrix::findKnots() 
{
	for (auto id = 0; id < numOfStops(); id++)
	{
		auto numOfPrecStops = _numOfPrecStops(id);
		int precStop;
		switch (numOfPrecStops)
		{
		case 0:
			m_allstops[id].setKnot();
			m_allstops[id].setTerminus();
			break;
		case 1:
			precStop = _PrecStopId(id);
			if (_isNumOfLinesSameAsPrec(id, precStop))
			{
				m_allstops[id].setKnot();
				_precStopUnKnot(precStop);
			}
			break;
		default:
			m_allstops[id].setKnot();
			break;
		}
	}
}
//Ilosc poprzedzajacych przystanek przystankow
int CconnectionMatrix::_numOfPrecStops(int& id) const
{
	int counter=0;
	for (auto &v : m_graphRepresentingStopsConnections)
	{
		if (_ifconjunction(v, id))
			counter++;
	}
	return counter;
}
//sprawdza czy jest jedynym nastepnikiem
bool CconnectionMatrix::_isNumOfLinesSameAsPrec(int &id, int &precId) const
{
	return (m_allstops[precId].numOfLines() == m_allstops[id].numOfLines()) ? true : false;
}
//usuwa flage wezel u poprzenika
void CconnectionMatrix::_precStopUnKnot(int &id)
{
	auto &ref = m_allstops[id];
	if (ref.isItKnot())
		ref.unsetKnot();
}
//sprawdza wartosc w grafie
bool CconnectionMatrix::_ifconjunction(const std::vector<CgraphKnot> &v, int &id) const
{
	return (v[id].m_conj == true) ? true : false;
}
//dla jednego poprzednika zwraca jego id
int CconnectionMatrix::_PrecStopId(int& id) const
{
	for (auto i = 0; i < m_numOfStops; ++i)
	{
		if (_ifconjunction(m_graphRepresentingStopsConnections[i], id))
			return i;
	}
	return id;
}
//referencja do przystanku
const CStop& CconnectionMatrix::getStopInfo(int i) const
{
	return m_allstops[i];
}
//referencja do lini
const CLine& CconnectionMatrix::getLineInfo(int i) const
{
	return m_allLines[i];
}
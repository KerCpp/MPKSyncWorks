#include "mpolaczen.h"
#include "_slaves.h"
#include <list>
#include <fstream>
#include <string>
#include <iostream>
/*
Konstruktor
fileName - nazwa pliku z danymi
*/
CconnectionMatrix::CconnectionMatrix(std::string fileName)
{
	std::ifstream DATA;
	DATA.open(fileName,std::ios::in);

	m_graphRepresentingStopsConnections.resize(30);
	for(auto &v : m_graphRepresentingStopsConnections)
		v.resize(400);

	if (DATA.is_open())
	{
		std::string actLineRoute = "";
		std::string actLineNum = "";
		Ctime transferTime(0, 0, 0);
		while (DATA.good())
		{
			CfileLine lineReader = CfileLine();
			DATA >> lineReader;
			int time = 0;
			if (actLineRoute==lineReader.m_route)
			{
				//dodawac przystanki do liniii!!!!!!!!!
				time = lineReader.m_transferTime - transferTime;
				_addStop(std::to_string(lineReader.m_stopId), time);
				transferTime = lineReader.m_transferTime;
			}
			else if (actLineNum==lineReader.m_lineId)
			{
				_addStop(std::to_string(lineReader.m_stopId), time, true);
				actLineRoute = lineReader.m_route;
				transferTime = lineReader.m_transferTime;
			}
			else
			{
				m_allLines.push_back(CLine(numOfLines(), lineReader.m_stopId));
				m_idLineTable.push_back(CidParser(m_idLineTable.size(), lineReader.m_lineId));
				m_numOfLines++;

				_addStop(std::to_string(lineReader.m_stopId), time, true);
				actLineNum = lineReader.m_lineId;
				actLineRoute = lineReader.m_route;
				transferTime = lineReader.m_transferTime;
			}
		}
	}
	else
	{
		std::cerr << "ERR_OPENING_FILE";
		std::cin.sync();
		std::cin.get();
		abort();
	}
	DATA.close();//kontrola zamkniêcia?
	//obciecie nadmiaru
	m_graphRepresentingStopsConnections.resize(m_numOfLines);
	m_graphRepresentingStopsConnections.shrink_to_fit();
	for (auto &v : m_graphRepresentingStopsConnections)
	{
		v.resize(m_numOfStops);
		v.shrink_to_fit();
	}
	for (auto &stop : m_allstops)
	{
		for (auto i = 0; i < m_numOfLines; i++)
		{
			if (m_graphRepresentingStopsConnections[i][stop.id()].m_conj = true)
				stop.addLine(i);
		}
	}
}
/*
Zwraca gdzie dana linia siê zatrzymuje
lineId -id lini
*/
std::vector<int> CconnectionMatrix::whereLineStops(const int lineId) const
{
	std::vector<int> tmpv;
	std::list<int> tmplist = m_allLines[lineId].stopsList();
	for (const auto &line : tmplist)
	{
		tmpv.push_back(int(line));
	}
	return tmpv;
}
/*
Zwraca jakie linie zatrzymuj¹ siê na wybranym przystanku
stopId-numer przystanku
*/
std::vector<int> CconnectionMatrix::whichLineStopsHere(const int stopId) const
{
	return m_allstops[stopId].lineList();
}
/*
Czy linia zatrzymuje sie na przystanku
*/
bool CconnectionMatrix::ifLineStopsHere(const int line, const int stop) const
{
	return m_graphRepresentingStopsConnections[line][stop].m_conj;
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
// zwraca czas pojazdu pomiedzy przystankiem aktualnym i go poprzedzajacym
int CconnectionMatrix::transferTime(int prev, int actual) const
{
	if (m_graphRepresentingStopsConnections[prev][actual].m_conj)
	return m_graphRepresentingStopsConnections[prev][actual].m_transferTime;
	else return 0;
}
//dlugosc taktu
int& CconnectionMatrix::period()
{
	return m_period;
}
//dopuszczalne opoznienie
int& CconnectionMatrix::delay()
{
	return m_delay;
}
//dlugosc taktu
int CconnectionMatrix::period() const
{
	return m_period;
}
//dopuszczalne opoznienie
int CconnectionMatrix::delay() const
{
	return m_delay;
}

//sprawdza czy przystanek juz jest dodany
bool CconnectionMatrix::_stopNotExist(const std::string &Id, int* ipId)
{
	for (const auto &Cid : m_idStopTable)
	{
		if (Cid.m_orgName == Id)
		{
			*ipId = Cid.m_programId;
			return false;
		}
	}
	return true;
}

//sprawdza czy istnieje i opcjonalnie dodaje przystanek
void CconnectionMatrix::_addStop(const std::string & Id, int time, bool terminus)
{
	int ipId = 0;//inside program ID
	if (_stopNotExist(Id, &ipId))
	{
		m_idStopTable.push_back(CidParser(m_idStopTable.size(),Id));
		m_allstops.push_back(CStop(m_idStopTable.size(), terminus));
		m_numOfStops++;
	}
	m_graphRepresentingStopsConnections[m_numOfLines - 1][ipId].m_conj = true;
	m_graphRepresentingStopsConnections[m_numOfLines - 1][ipId].m_transferTime = time;
}
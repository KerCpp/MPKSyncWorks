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
	DATA.open(fileName, std::ios::in);

	m_graphRepresentingStopsConnections.resize(400);
	m_graphRepresentingLineStopConnections.resize(400);
	for (auto &v : m_graphRepresentingStopsConnections)
		v.resize(400);
	for (auto &v : m_graphRepresentingLineStopConnections)
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
			int ipID = 0;
			int actLineID = numOfLines()-1;
			if (actLineRoute == lineReader.m_route)
			{
				time = lineReader.m_transferTime - transferTime;
				_addStop(std::to_string(lineReader.m_stopId));
				_stopNotExist(std::to_string(lineReader.m_stopId), &ipID);
				//m_allLines[_lineParser(lineReader.m_lineId)].stopsList().push_back(ls(ipID, time));
				m_allLines[actLineID].stopsList().push_back(ls(ipID, time));
				transferTime = lineReader.m_transferTime;
			}
			else if (actLineNum == lineReader.m_lineId)
			{
				_stopNotExist(std::to_string(lineReader.m_stopId), &ipID);
				m_allLines.push_back(CLine(numOfLines(), ipID));
				m_idLineTable.push_back(CidParser(m_idLineTable.size(), lineReader.m_lineId));
				m_numOfLines++;
				_addStop(std::to_string(lineReader.m_stopId), true);
				/*
				_stopNotExist(std::to_string(lineReader.m_stopId), &ipID);
				m_allLines[actLineID].stopsList().push_back(ls(ipID, time));
				*/
				actLineRoute = lineReader.m_route;
				transferTime = lineReader.m_transferTime;
			}
			else
			{
				_stopNotExist(std::to_string(lineReader.m_stopId), &ipID);
				m_allLines.push_back(CLine(numOfLines(), ipID));
				m_idLineTable.push_back(CidParser(m_idLineTable.size(), lineReader.m_lineId));
				m_numOfLines++;
				_addStop(std::to_string(lineReader.m_stopId), true);
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
	_fillGraph();
	_resizeGraphs();
	_fillStops();
}
/*
Zwraca gdzie dana linia siê zatrzymuje
lineId -id lini
*/
std::vector<int> CconnectionMatrix::whereLineStops(const int lineId) const
{
	std::vector<int> tmpv;
	std::list<ls> tmplist = m_allLines[lineId].stopsList();
	for (const auto &line : tmplist)
	{
		tmpv.push_back(int(line.m_id));
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
	//return m_graphRepresentingStopsConnections[line][stop].m_conj;
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
	*ipId = m_numOfStops;
	return true;
}

//sprawdza czy istnieje i opcjonalnie dodaje przystanek
void CconnectionMatrix::_addStop(const std::string & Id, bool terminus)
{
	int ipId = 0;//inside program ID
	if (_stopNotExist(Id, &ipId))
	{
		int size = m_idStopTable.size();
		m_idStopTable.push_back(CidParser(size,Id));
		m_allstops.push_back(CStop(size, terminus));
		m_numOfStops++;
	}
	m_graphRepresentingLineStopConnections[m_numOfLines - 1][ipId] = true;
	//m_graphRepresentingStopsConnections[m_numOfLines - 1][ipId].m_conj = true;
	//m_graphRepresentingStopsConnections[m_numOfLines - 1][ipId].m_transferTime = time;
}

//zwraca ipID linii
int CconnectionMatrix::_lineParser(std::string ID) const
{
	for (const auto &Cid : m_idLineTable)
	{
		if (Cid.m_orgName == ID)
			return Cid.m_programId;
	}
	return m_numOfLines;
}
//wypelnia graf przystankow - co z czym jest polaczone
void CconnectionMatrix::_fillGraph()
{
	for (auto &line : m_allLines)
	{
		if (line.stopsList().size() == 1)
			continue;
		auto it = line.stopsList().begin();
		auto itNext = line.stopsList().begin();
		itNext++;
		do
		{
			m_graphRepresentingStopsConnections[(*it).m_id][(*itNext).m_id].m_conj = true;
			m_graphRepresentingStopsConnections[(*it).m_id][(*itNext).m_id].m_transferTime = (*itNext).m_startTime;
			it++;
			itNext++;
		} while (itNext != line.stopsList().end());
	}
}
//wypelnai linie ktore zatrzymuja sie na przystanku
void CconnectionMatrix::_fillStops()
{
	for (auto &stop : m_allstops)
	{
		for (auto i = 0; i < m_numOfLines; i++)
		{
			if (m_graphRepresentingLineStopConnections[i][stop.id()] == true)
				stop.addLine(i);
		}
	}
	//puste miejsca na poszczegolne linie
	for (auto &stop : m_allstops)
		stop.setTTable().resize(stop.numOfLines());
}
//obcina grafy do minimum
void CconnectionMatrix::_resizeGraphs()
{
	m_graphRepresentingLineStopConnections.resize(m_numOfLines);
	m_graphRepresentingLineStopConnections.shrink_to_fit();
	m_graphRepresentingStopsConnections.resize(m_numOfStops);
	m_graphRepresentingStopsConnections.shrink_to_fit();
	for (auto &v : m_graphRepresentingLineStopConnections)
	{
		v.resize(m_numOfStops);
		v.shrink_to_fit();
	}
	for (auto &v : m_graphRepresentingStopsConnections)
	{
		v.resize(m_numOfStops);
		v.shrink_to_fit();
	}
}
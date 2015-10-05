#include "grupa.h"
#include "_slaves.h"
#include "mpolaczen.h"
#include <algorithm>
#include <iostream>

/*
Konstruktor, tworz¹cy grupê lini o wspólnych przystankach w oparciu o liniê bazow¹
*/
Cgroup::Cgroup(const int &rootID, const CconnectionMatrix &m) : m_matrix(m)
{
	m_idsOfLines.push_back(rootID);//linia bazowa
	std::vector<int> stops = m_matrix.whereLineStops(rootID);//przystanki bazowej
	auto ctrlLines = 1;
	auto ctrlStops = stops.size();
	auto errctrl=0;
	while (errctrl++ < m_matrix.numOfLines())
	{
		for each  (auto &SId in stops)
		{
			std::vector<int> lineId = m_matrix.whichLineStopsHere(SId);//wszystkie linie dla przystankow
			for each  (const int &LId in lineId)
				_add(LId);//dodawanie lini dla tych przystankow o ile nie ma
		}
		if (numOfLines() == ctrlLines) return;//nie bylo lini do dodania
		else ctrlLines = numOfLines();
		// to samo ale na odwrot
		stops = whereLinesStops();
		if (stops.size() == ctrlStops) return; //nie dodano przystanku
		else ctrlStops = stops.size();
	}
	std::cerr << "ERR_TOO_MUCH_ITERACJI";
}
/*
Funkcja dodaj¹ca element do grupy
*/
void Cgroup::_add(const int& id)
{
	if (!onlyOnceRuleCtrl(id,m_idsOfLines))	
		m_idsOfLines.push_back(id);
}
/*
Funkcja zwraca elementy w grupie
*/
std::vector<int> const& Cgroup::groupMembers() const
{
	return m_idsOfLines;
}
/*
Zwraca wielkoœæ grupy
*/
int Cgroup::numOfLines() const
{
	return m_idsOfLines.size();
}
/*
Zwraca pulê przystanków w oparciu o linie
*/
std::vector<int> Cgroup::whereLinesStops() const
{
	std::vector<int> stops;
	for each (auto &LId in m_idsOfLines)
	{
		const std::vector<int> &tmp = m_matrix.whereLineStops(LId);
		for each  (auto &SId in tmp)
		{
			if (!onlyOnceRuleCtrl(SId, stops))
				stops.push_back(SId);
		}
	}
	return stops;
}


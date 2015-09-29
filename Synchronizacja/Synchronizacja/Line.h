#pragma once
#include <list>

class CLine
{
	int m_id=0;
	std::list<int> m_stops;
public:
	CLine::CLine() : m_id(0), m_stops(){}
	CLine(int num, int stop) : m_id(num){ m_stops.push_back(stop); }
	~CLine(){}
	const int lineID() const;
	std::list<int> const& stopsList() const;
	std::list<int>& stopsList();
};


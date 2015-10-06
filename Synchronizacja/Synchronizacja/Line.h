#pragma once
#include <list>
#include "_slaves.h"

class CLine
{
	int m_id=0;
	//std::list<int> m_stops;
	std::list<ls> m_stops;
public:
	CLine::CLine() : m_id(0), m_stops(){}
	CLine(int num, int stop) : m_id(num){ m_stops.push_back(ls(stop, 0)); }
	~CLine(){}
	const int lineID() const;
	std::list<ls> const& stopsList() const;
	std::list<ls>& stopsList();
};


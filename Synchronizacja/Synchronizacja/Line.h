#pragma once
#include <list>

class CLine
{
	int m_id;
	std::list<int> m_stops;
public:
	CLine();
	~CLine();
	int lineID(){};
	std::list<int> const& stopsList() const;
};


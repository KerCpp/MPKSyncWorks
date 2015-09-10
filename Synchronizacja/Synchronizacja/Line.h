#pragma once
#include <list>

class CLine
{
	int m_id=0;
	std::list<int> m_stops;
public:
	CLine();
	~CLine();
	const int lineID() const;
	std::list<int> const& stopsList() const;
};


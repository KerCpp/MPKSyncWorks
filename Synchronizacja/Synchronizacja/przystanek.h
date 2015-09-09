#pragma once
#include <vector>

class CStop
{
	int m_id = 0;
	bool m_knot = false;
	bool m_terminus = false;
	std::vector<int> m_lines = {};
public:
	CStop();
	virtual ~CStop();
	bool isItTerminus() const;
	bool isItKnot() const;
	void setKnot();
	void unsetKnot();
	void setTerminus();
	void unsetTerminus();
	const int numOfLines() const;
	const int id() const;
};


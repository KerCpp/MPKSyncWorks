#pragma once
#include <vector>

class CStop
{
	int m_id;
	bool m_knot = false;
	bool m_terminus = false;
	std::vector<int> m_lines;
public:
	CStop();
	virtual ~CStop();
	bool isItTerminus() const{ return 1; }
	bool isItKnot() const{ return 1; }
	void setKnot(){}
	void unsetKnot(){}
	void setTerminus(){}
	void unsetTerminus(){}
	int numOfLines() const{ return 1; }
	int id() const { return m_id; }
};


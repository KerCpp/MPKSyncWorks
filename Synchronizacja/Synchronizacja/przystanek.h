#pragma once
#include <vector>

class CStop
{
	int m_id = 0;
	bool m_knot = false;
	bool m_terminus = false;
	std::vector<int> m_lines = {};
	std::vector<int> m_tTable = {};
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
	int rating() const;
	const std::vector<int>& setTTable();
private:
	int _cumPowSum(const std::vector<int>&) const;
};


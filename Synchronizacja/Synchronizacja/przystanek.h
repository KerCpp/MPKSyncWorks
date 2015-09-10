#pragma once
#include <vector>
#include "_slaves.h"

class CStop
{
	int m_id = 0;
	bool m_knot = false;
	bool m_terminus = false;
	std::vector<int> m_lines = {};
	std::vector<ls> m_tTable = {};
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
	const std::vector<ls>& setTTable();
	const std::vector<ls>& setTTable() const;
	bool isGood() const;
private:
	int _cumPowSum(const std::vector<int>&) const;
};


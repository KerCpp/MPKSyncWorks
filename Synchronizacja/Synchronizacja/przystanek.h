#pragma once
#include <vector>
#include "_slaves.h"

class CStop
{
	int m_id = 0;
	bool m_knot = false;
	bool m_terminus = false;
	std::vector<int> m_lines;
	std::vector<ls> m_tTable;
public:
	CStop(): m_lines(), m_tTable(){}
	CStop(int Id, bool terminus) : CStop(){ m_id = Id; m_terminus = terminus; }
	~CStop(){}
	bool isItTerminus() const;
	bool isItKnot() const;
	void setKnot();
	void unsetKnot();
	void setTerminus();
	void unsetTerminus();
	const int numOfLines() const;
	const int id() const;
	int rating() const;
	std::vector<ls>& setTTable();
	const std::vector<ls>& setTTable() const;
	bool isGood() const;//dopisac costam
	void addLine(int id);
	const std::vector<int>& lineList() const;

private:
	int _cumPowSum(const std::vector<int>&) const;
};


#pragma once
#include <vector>
#include "mpolaczen.h"
class Cgroup 
{
	std::vector<int> m_idsOfLines;
	const CconnectionMatrix &m_matrix;
public:
	Cgroup(const int&,const CconnectionMatrix&);
	~Cgroup(){};
	std::vector<int> const& groupMembers() const;
	int numOfLines() const;
	std::vector<int> whereLinesStops() const;
private:
	inline void _add(const int&);
};


#pragma once
#include "Line.h"
#include "KnotNet.h"
#include <vector>

struct ls//line start
{
	CLine m_id();
	int m_startTime=0;
};
//osobnik
class individual
{
	std::vector<ls> m_lsVect;
public:
	individual();
	individual(const CKnotNet&);
	individual(const individual&);
	~individual();
	void operator+=(const individual&);
	friend std::ostream& operator<<(const std::ostream& out, const individual& rhs);
};


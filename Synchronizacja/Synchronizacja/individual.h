#pragma once
#include "Line.h"
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
	~individual();
};


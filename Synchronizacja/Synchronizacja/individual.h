#pragma once
#include "Line.h"
#include "KnotNet.h"
#include <vector>

struct ls//line start
{
	int m_id();
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
	individual operator+=(const individual&);
	friend std::ostream& operator<<(std::ostream& out, const individual& rhs);
	const std::vector<ls>& retGenom() const;
};


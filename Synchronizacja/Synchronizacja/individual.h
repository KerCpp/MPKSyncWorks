#pragma once
#include "Line.h"
#include "KnotNet.h"
#include "mpolaczen.h"
#include "_slaves.h"
#include <vector>


//osobnik
class individual
{
	std::vector<ls> m_lsVect;
public:
	individual();
	individual(const CKnotNet&, const CconnectionMatrix&);
	//individual(const individual&); automatyczny
	~individual();
	individual operator+=(const individual&);
	friend std::ostream& operator<<(std::ostream& out, const individual& rhs);
	const std::vector<ls>& retGenom() const;
};


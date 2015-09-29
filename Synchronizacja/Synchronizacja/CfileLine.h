#pragma once
#include "_slaves.h"
#include <string>
#include <iostream>

class CfileLine
{
public:
	std::string m_lineId = "";
	std::string m_route = "";
	int m_stopId = 0;
	std::string m_stopName = "";
	Ctime m_transferTime;
	CfileLine() : m_transferTime(0, 0, 0){}
	~CfileLine(){}
	friend const std::istream& operator>>(std::istream&, CfileLine &);
};


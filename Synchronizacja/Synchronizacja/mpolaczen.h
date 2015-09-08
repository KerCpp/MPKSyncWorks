#pragma once
#include "Line.h"
#include "przystanek.h"
#include <vector>
#include <string>

struct CgraphKnot
{
	bool m_conj = false;
	int m_transferTime = 0;
};

class CconnectionMatrix
{
	std::vector<std::vector<bool> > m_table;
	std::vector<std::vector<CgraphKnot> > m_graphRepresentingStopsConnections;
	int m_numOfLines = 0;
	int m_numOfStops = 0;
	std::vector<CLine> m_allLines;
	std::vector<CStop> m_allstops;
public:
	CconnectionMatrix(){};
	CconnectionMatrix(std::string fileName);
	~CconnectionMatrix(){};
	std::vector<int> whereLineStops(const int&) const;
	std::vector<int> whichLineStopsHere(const int &) const;
	inline bool ifLineStopsHere(const int &, const int &) const;
	int numOfLines() const;
	int numOfStops() const;
	void findKnots();
	CStop getStopInfo(int) const;//return m_allStops[int];
	CLine getLineInfo(int) const;
private:
	void _fillGraph();
	int _numOfPrecStops(int&) const;
	int _PrecStopId(int&) const;
	bool _isNumOfLinesSameAsPrec(int&, int&) const;
	void _precStopUnKnot(int&);
	bool _ifconjunction(const std::vector<CgraphKnot>&, int&) const;
};


#pragma once
#include "Line.h"
#include "przystanek.h"
#include "CfileLine.h"
#include "_slaves.h"
#include <vector>
#include <string>

class CconnectionMatrix
{
	std::vector<std::vector<bool> > m_graphRepresentingLineStopConnections;
	std::vector<std::vector<CgraphKnot> > m_graphRepresentingStopsConnections;
	int m_numOfLines = 0;
	int m_numOfStops = 0;
	std::vector<CLine> m_allLines;
	std::vector<CStop> m_allstops;
	std::vector<CidParser> m_idLineTable;
	std::vector<CidParser> m_idStopTable;
	std::vector<loopLine> m_loops;
	int m_period = 30;
	int m_delay = 0;
public:
	CconnectionMatrix(){};
	CconnectionMatrix(std::string fileName);
	~CconnectionMatrix(){};
	std::vector<int> whereLineStops(const int) const;
	std::vector<int> whichLineStopsHere(const int) const;
	inline bool ifLineStopsHere(const int, const int) const;
	int numOfLines() const;
	int numOfStops() const;
	void findKnots();
	const CStop& getStopInfo(int) const;
	const CLine& getLineInfo(int) const;
	int transferTime(int, int) const;
	int period() const;
	int delay() const;
	int& period();
	int& delay();
	std::vector<loopLine> retLoops() const;
private:
	void _fillGraph();
	void _fillStops();
	void _resizeGraphs();
	int _numOfPrecStops(int&) const;
	int _PrecStopId(int&) const;
	bool _isNumOfLinesSameAsPrec(int&, int&) const;
	void _precStopUnKnot(int&);
	bool _ifconjunction(const std::vector<CgraphKnot>&, int&) const;
	bool _stopNotExist(const std::string&, int*);
	void _addStop(const std::string&, bool=false);
	int _lineParser(std::string) const;
	void _updateLoops();
	void _ulHelp(loopLine&,int);
};

